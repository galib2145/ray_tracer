#include <iostream>
#include <cmath>

class Vec3
{
    public:
        float x,y,z;
        Vec3(float x,float y,float z){
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Vec3(){
            x=0.0;
            y=0.0;
            z=0.0;
        }

        float dot(Vec3 v){
            return x*v.x + y*v.y + z*v.z;
        }

        float magnitude(){
            return (float)sqrt(x*x + y*y + z*z);
        }

        void normalize(){
            float magnitude_value = magnitude();
            x = (float)x / magnitude_value;
            y = (float)y / magnitude_value;
            z = (float)z /magnitude_value;
        }

        Vec3 operator - (Vec3 operand){
            return Vec3(x-operand.x,y-operand.y,z-operand.z);
        }

        Vec3 operator + (Vec3 operand){
            return Vec3(x+operand.x,y+operand.y,z+operand.z);
        }

        Vec3 operator * (float scalar){
            return Vec3(x*scalar,y*scalar,z*scalar);
        }

        float get_unit_dot_product(Vec3 second_vector){
            this->normalize();
            second_vector.normalize();
            return (*this).dot(second_vector);
        }

        void print_vector(){
            std::cout<<"x is :"<<x<<std::endl;
            std::cout<<"y is :"<<y<<std::endl;
            std::cout<<"z is :"<<z<<std::endl;
        }
};
