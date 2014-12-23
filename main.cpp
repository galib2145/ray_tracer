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

class RenderContext{
    public:
        Camera camera;
        int image_width, image_height;
        float aspect_ratio;
        Vec3 background_color;
        vector<Object> scene;

        RenderContext(float width, float height, float fov){
            image_height = height;
            image_width = width;
            aspect_ratio = (float)image_width/image_height;
            background_color = Vec3(0.2, 0.3, 0.5);
        }

        void add_object_to_scene(Object object){
            scene.push_back(object);
        }
};

Vec3 trace(vector<Object> scene, Ray ray, Vec3 background_color){
    Object *object_closest_hit;
    bool if_hit = false;
    float t_closest_hit;
    float t_hit;

    for (std::vector<Object>::iterator it = scene.begin() ; it != scene.end(); ++it){
        Object object = *it;
        if(object.intersect(ray,t_hit)){
            if(t_hit<t_closest_hit){
                if_hit = true;
                t_closest_hit = t_hit;
                *object_closest_hit = object;
            }
        }
    }

    if(if_hit){
        return (*object_closest_hit).color;
    }

    return background_color;
}

void add(){
}

void render(RenderContext context){
    char *buffer = new char[context.image_width * context.image_height * 3];
    char *pix = buffer;
    memset(buffer, 0x0, sizeof(char) * context.image_width * context.image_height);
    Sphere sphere(Vec3(0,0,-10),5);
    Vec3 ray_origin;

    for(int j=0;j<context.image_height;++j){
        for(int i=0;i<context.image_width;i++,pix+=3){
            float x_remapped = (2 * (i + 0.5) / context.image_width - 1) * context.camera.fov_range * context.aspect_ratio;
            float y_remapped = (1 - 2 * (j + 0.5) / context.image_height) * context.camera.fov_range * context.aspect_ratio;
            Vec3 ray_direction = context.camera.world_to_camera_matrix.mulitply_direction_by_matrix(Vec3(x_remapped,y_remapped,-1));
            ray_direction.normalize();
            float t;
            Ray ray(ray_origin, ray_direction);

            bool intersects = sphere.intersect(ray,t);
            if(!intersects){
                pix[0] = (unsigned char)(255);
                pix[1] = (unsigned char)(255);
                pix[2] = (unsigned char)(255);
            }
            else{
                pix[0] = (unsigned char)(255 * sphere.color.x);
                pix[1] = (unsigned char)(255 * sphere.color.y);
                pix[2] = (unsigned char)(255 * sphere.color.z);
            }
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
    RenderContext rc(1920,1080,60);
    render(rc);

    cout<<"Hello!"<<endl;
    cin.get();
    return 0;
}

