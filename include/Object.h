#include <stdlib.h>

class Object
{
    public:
        Vec3 color;
        Mat4 object_to_world_matrix;
        Mat4 world_to_object_matrix;

        Object(Mat4 object_to_world_matrix, Vec3 color){
            this->color = color;
            this->object_to_world_matrix = object_to_world_matrix;
            world_to_object_matrix = object_to_world_matrix.get_inverse();
        }

        virtual bool intersect(Ray ray, float t){
            return true;
        }
};


