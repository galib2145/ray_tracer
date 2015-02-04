#include <limits>
#include <iostream>

using namespace std;

typedef enum ray_type{
    unknown_ray=0,
    camera_ray,
    shadow_ray
};

class Ray
{
    public:
        Vec3 origin,direction;
        float t_min,t_max;

        Ray(Vec3 origin, Vec3 direction){
            this->origin = origin;
            this->direction = direction;
            t_min = float(0);
            t_max = std::numeric_limits<float>::max();
        }

        Vec3 get_point(float t){
            return origin + direction*t;
        }

        void print_ray(){
            cout<<endl<<"Ray data:"<<endl;
            cout<<"Origin vector:"<<endl;
            origin.print_vector();
            cout<<"Direction vector:"<<endl;
            direction.print_vector();
        }
};

