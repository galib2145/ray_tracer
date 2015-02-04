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

#define MAX_RAY_DEPTH 5

using namespace std;

class Light_source
{
public:
    Vec3 position;
    Vec3 color;
    float intensity;

    Light_source(Vec3 light_position, Vec3 light_color,float light_intensity)
    {
        this->position = light_position;
        this->color = light_color;
        this->intensity = light_intensity;
    }
};

class RenderContext
{
public:
    Camera camera;
    int image_width, image_height;
    float aspect_ratio;
    Vec3 background_color;
    vector<Object*> objects;
    vector<Light_source> light_sources;

    RenderContext(float width, float height, float fov, vector<Object*> objects, vector<Light_source>& input_light_sources)
    {
        image_height = height;
        image_width = width;
        aspect_ratio = (float)image_width/image_height;
        background_color = Vec3(.39, .58, .93);
        this->objects = objects;
        this->light_sources = input_light_sources;
    }
};

float mix(float a, float b, float mix){
    return b * mix + a * (float(1) - mix);
}

Vec3 trace(vector<Object*> objects, vector<Light_source> light_sources, Ray ray,int depth)
{
    Object* object_closest_hit;
    bool if_hit = false;
    float t_closest_hit = 1000;
    float t_hit;

    for (int i=0; i<objects.size(); i++)
    {
        Object* object = objects[i];
        if(object->intersect(ray,t_hit))
        {
            if(t_hit<t_closest_hit)
            {
                if_hit = true;
                t_closest_hit = t_hit;
                object_closest_hit = object;
            }
        }
    }

    if(if_hit)
    {
        Vec3 closest_hit_point = ray.get_point(t_closest_hit);

        if(depth < MAX_RAY_DEPTH)
        {
            Vec3 reflection_color, refraction_color;
            Vec3 normal_at_hit = object_closest_hit->get_normal_at_point(closest_hit_point);
            float facing_ratio = -ray.direction.dot(normal_at_hit);
            float fresnel_effect = mix(pow(1 - facing_ratio, 3), 1, 0.1);

            if(object_closest_hit->reflectance > 0){
                Vec3 reflection_direction = (normal_at_hit * (normal_at_hit.dot(ray.direction))) * 2.0 - ray.direction;
                reflection_direction.normalize();
                Ray reflected_ray(closest_hit_point,reflection_direction);
                Vec3 reflection_color =  trace(objects,light_sources,reflected_ray,depth+1);
            }

            if(object_closest_hit->transparency > 0){
                float eta = (float)1)/1.1;
                float cosi = -normal_at_hit.dot(ray.direction);
                float k = 1 - eta * eta * (1 - cosi * cosi);
                Vec3 refraction_direction = ray.direction * eta + normal_at_hit * (eta *  cosi - sqrt(k));
                refraction_direction.normalize();
                Ray refracted_ray(closest_hit_point, refraction_direction);
                Vec3 refraction_color = tracetrace(objects, light_sources, refracted_ray, depth+1);
            }


        }

        return object_closest_hit->color;
    }

    return 0;
}

void render_image_from_buffer(char *buffer, RenderContext context)
{
    std::ofstream ofs;
    ofs.open("./untitled.ppm");
    ofs << "P6\n" << context.image_width << " " << context.image_height << "\n255\n";
    ofs.write((char*)buffer, sizeof(unsigned char) * context.image_width * context.image_height * 3);
    ofs.close();
    delete [] buffer;
}

void render(RenderContext context)
{
    char *buffer = new char[context.image_width * context.image_height * 3];
    char *pix = buffer;
    memset(buffer, 0x0, sizeof(char) * context.image_width * context.image_height);
    Vec3 ray_origin;

    for(int j=0; j<context.image_height; ++j)
    {
        for(int i=0; i<context.image_width; i++,pix+=3)
        {
            float x_remapped = (2 * (i + 0.5) / context.image_width - 1) * context.camera.fov_range * context.aspect_ratio;
            float y_remapped = (1 - 2 * (j + 0.5) / context.image_height) * context.camera.fov_range * context.aspect_ratio;
            Vec3 ray_direction = context.camera.world_to_camera_matrix.mulitply_direction_by_matrix(Vec3(x_remapped,y_remapped,-4));
            ray_direction.normalize();
            float t;
            Ray ray(ray_origin, ray_direction);
            Vec3 color = trace(context.objects, context.light_sources, ray, 0);
            pix[0] = (unsigned char)(255 * color.x);
            pix[1] = (unsigned char)(255 * color.y);
            pix[2] = (unsigned char)(255 * color.z);
        }
    }

    render_image_from_buffer(buffer,context);
}

int main()
{
    vector<Object*> objects;
    vector<Light_source> light_sources;
    Light_source light_source_one = Light_source(Vec3(-20,50,10),Vec3(0,1,0),.6);
    light_sources.push_back(light_source_one);
    Light_source light_source_two = Light_source(Vec3(-10,10,10),Vec3(1,0,0),.2);
    light_sources.push_back(light_source_two);
    Light_source light_source_three = Light_source(Vec3(-100,30,-5),Vec3(1,0,0),.5);
    light_sources.push_back(light_source_three);

    Sphere sphere_two(Vec3(0, 0, -20),4,Vec3(1,.32,.36),0);
    objects.push_back(&sphere_two);
    Sphere sphere_three(Vec3(5, -1, -15),2,Vec3(.90,.76,.46),0);
    objects.push_back(&sphere_three);
    Sphere sphere_four(Vec3(5, 0, -25),3,Vec3(.65,.77,.97),0);
    objects.push_back(&sphere_four);
    Sphere sphere_five(Vec3(5, -1, -15),2,Vec3(.90,.76,.46),0);
    objects.push_back(&sphere_five);
    cout<<objects.size()<<endl;
    cout<<light_sources.size()<<endl;
    RenderContext rc(1920,1080,60,objects,light_sources);
    render(rc);

    cout<<"Hello me!"<<endl;
    cin.get();
    return 0;
}

