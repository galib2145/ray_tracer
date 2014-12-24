#include <iostream>
#include <cstring>
#include <Vec3.h>
#include <cmath>
#include <Mat4.h>
#include <Ray.h>
#include <fstream>
#include <Object.h>
#include <Sphere.h>
#include <Camera.h>
#include <vector>

using namespace std;

class Light_source{
    public:
        Vec3 position;
        Vec3 color;

        Light_source(Vec3 position, Vec3 color){
            this->position = position;
            this->color = color;
        }
};

class RenderContext{
    public:
        Camera camera;
        int image_width, image_height;
        float aspect_ratio;
        Vec3 background_color;
        vector<Sphere> objects;
        vector<Light_source> light_sources;

        RenderContext(float width, float height, float fov, vector<Sphere> objects, vector<Light_source> light_sources){
            image_height = height;
            image_width = width;
            aspect_ratio = (float)image_width/image_height;
            background_color = Vec3(1, 1, 1);
            this->objects = objects;
            this->light_sources = light_sources;
        }

        void print_objects_info(){
            for (std::vector<Sphere>::iterator it = objects.begin() ; it != objects.end(); ++it){
                Sphere object = *it;
                object.print();
            }
        }

        void add_object_to_objects(Sphere object){
            objects.push_back(object);
        }
};

Vec3 trace(vector<Sphere> objects, vector<Light_source> light_sources, Ray ray, Vec3 background_color){
    Sphere object_closest_hit(Vec3(0,0,-10),5,Vec3(.2,.2,.5));
    bool if_hit = false;
    float t_closest_hit = 1000;
    float t_hit;

    for (int i=0; i<objects.size();i++){
        Sphere object = objects[i];
        if(object.intersect(ray,t_hit)){
            if(t_hit<t_closest_hit){
                if_hit = true;
                t_closest_hit = t_hit;
                object_closest_hit = object;
            }
        }
    }

    if(if_hit){
        return (object_closest_hit).color;
    }

    return background_color;
}

void render(RenderContext context){
    context.print_objects_info();
    char *buffer = new char[context.image_width * context.image_height * 3];
    char *pix = buffer;
    memset(buffer, 0x0, sizeof(char) * context.image_width * context.image_height);
    Vec3 ray_origin;

    for(int j=0;j<context.image_height;++j){
        for(int i=0;i<context.image_width;i++,pix+=3){
            float x_remapped = (2 * (i + 0.5) / context.image_width - 1) * context.camera.fov_range * context.aspect_ratio;
            float y_remapped = (1 - 2 * (j + 0.5) / context.image_height) * context.camera.fov_range * context.aspect_ratio;
            Vec3 ray_direction = context.camera.world_to_camera_matrix.mulitply_direction_by_matrix(Vec3(x_remapped,y_remapped,-3));
            ray_direction.normalize();
            float t;
            Ray ray(ray_origin, ray_direction);
            Vec3 color = trace(context.objects, context.light_sources, ray, context.background_color);
            pix[0] = (unsigned char)(255 * color.x);
            pix[1] = (unsigned char)(255 * color.y);
            pix[2] = (unsigned char)(255 * color.z);
        }

    }

    std::ofstream ofs;
    ofs.open("./untitled.ppm");
    ofs << "P6\n" << context.image_width << " " << context.image_height << "\n255\n";
    ofs.write((char*)buffer, sizeof(unsigned char) * context.image_width * context.image_height * 3);
    ofs.close();
    delete [] buffer;
}

int main()
{
    vector<Sphere> objects;
    vector<Light_source> light_sources;
    Light_source light_source_one = Light_source(Vec3(0,4,0),Vec3(0.2,0.5,0.6));
    light_sources.push_back(light_source_one);
    Sphere sphere_one(Vec3(0, -10004, -20),10000,Vec3(.2,.2,.2));
    Sphere sphere_two(Vec3(0, 0, -20),4,Vec3(1,.32,.36));
    Sphere sphere_three(Vec3(5, -1, -15),2,Vec3(.90,.76,.46));
    Sphere sphere_four(Vec3(5, 0, -25),3,Vec3(.65,.77,.97));
    Sphere sphere_five(Vec3(5, -1, -15),2,Vec3(.90,.76,.46));
    objects.push_back(sphere_one);
    objects.push_back(sphere_two);
    objects.push_back(sphere_three);
    objects.push_back(sphere_four);
    objects.push_back(sphere_five);
    cout<<objects.size()<<endl;
    RenderContext rc(640,480,60,objects,light_sources);
    render(rc);

    cout<<"Hello me!"<<endl;
    cin.get();
    return 0;
}

