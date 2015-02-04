class Sphere : public Object
{
    public:
        Vec3 center;
        float radius,radius2;

        Sphere(Vec3 center, float radius, Vec3 color, float reflective_property, Mat4 object_to_world_matrix = Mat4::Identity) : Object(object_to_world_matrix,color)
        {
            this->center = object_to_world_matrix.multiply_vector_by_matrix(center);
            this->radius = radius;
            this->radius2 = radius*radius;
        }

        bool intersect(Ray ray, float &t){
            float t0,t1;
            Vec3 L = center - ray.origin;
            float tca = L.dot(ray.direction);
            if (tca < 0) return false;
            float d2 = L.dot(L) - tca * tca;
            if (d2 > radius2) return false;
            float thc = sqrt(radius2 - d2);
            t0 = tca - thc;
            t1 = tca + thc;
            if (t0 > ray.t_max) return false;
            if (t1 < t0) std::swap(t0, t1);
            t = (t0 < 0) ? t1 : t0;
            return true;
        }

        Vec3 get_normal_at_point(Vec3 point){
            return point - center;
        }

        void print(){
            cout<<"radius : "<<radius<<endl;
        }
};


