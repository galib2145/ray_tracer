#include <stdlib.h>

class Object
{
    public:
        Vec3 color;
        float reflective_property;
        Mat4 object_to_world_matrix;
        Mat4 world_to_object_matrix;
        float kd = 0.6, ks = 0.4;

        Object(Mat4 object_to_world_matrix, Vec3 color, float reflective_property=0){
            this->color = color;
            this->object_to_world_matrix = object_to_world_matrix;
            this->reflective_property = reflective_property;
            world_to_object_matrix = object_to_world_matrix.get_inverse();
        }

        virtual bool intersect(Ray ray, float &t) = 0;

        virtual Vec3 get_normal_at_point(Vec3 point) = 0;

        virtual void print(){
        }
};


