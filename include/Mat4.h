#include <iostream>

class Mat4
{
    public:
        float m[4][4];
        static const Mat4 Identity;

        Mat4()
        {
            m[0][0] = 1.0;
            m[0][1] = 0.0;
            m[0][2] = 0.0;
            m[0][3] = 0.0;
            m[1][0] = 0.0;
            m[1][1] = 1.0;
            m[1][2] = 0.0;
            m[1][3] = 0.0;
            m[2][0] = 0.0;
            m[2][1] = 0.0;
            m[2][2] = 1.0;
            m[2][3] = 0.0;
            m[3][0] = 0.0;
            m[3][1] = 0.0;
            m[3][2] = 0.0;
            m[3][3] = 1.0;
        }

        void input_matrix(){
            std::cout<<"enter the matrix:"<<std::endl;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    std::cin>>m[i][j];
                }
            }
        }

        void scale(float scale_factor){
            m[0][0]*= scale_factor;
            m[1][1]*= scale_factor;
            m[2][2]*= scale_factor;
        }

        void scaleX(float x){
            m[0][0]*= x;
        }

        void scaleY(float y){
            m[1][1]*= y;
        }

        void scaleZ(float z){
            m[2][2]*= z;
        }

        Vec3 mulitply_direction_by_matrix(Vec3 source_vector)
        {
            Vec3 destination_vector;
            destination_vector.x = source_vector.x * m[0][0] + source_vector.y * m[1][0] + source_vector.z * m[2][0];
            destination_vector.y = source_vector.x * m[0][1] + source_vector.y * m[1][1] + source_vector.z * m[2][1];
            destination_vector.z = source_vector.x * m[0][2] + source_vector.y * m[1][2] + source_vector.z * m[2][2];
            return destination_vector;
        }

        Vec3 multiply_vector_by_matrix(const Vec3 source_vector) const
        {
            Vec3 destination_vector;
            destination_vector.x = source_vector.x * m[0][0] + source_vector.y * m[1][0] + source_vector.z * m[2][0] + m[3][0];
            destination_vector.y = source_vector.x * m[0][1] + source_vector.y * m[1][1] + source_vector.z * m[2][1] + m[3][1];
            destination_vector.z = source_vector.x * m[0][2] + source_vector.y * m[1][2] + source_vector.z * m[2][2] + m[3][2];
            float w = source_vector.x * m[0][3] + source_vector.y * m[1][3] + source_vector.z * m[2][3] + m[3][3];
            if (w != 1 && w != 0) {
                destination_vector.x/= w;
                destination_vector.y/= w;
                destination_vector.z/= w;
            }

            return destination_vector;
        }

        Mat4 get_inverse(){
            int i, j, k;
            Mat4 s;
            Mat4 t = (*this);

            for (i = 0; i < 3 ; i++) {
                int pivot = i;
                float pivotsize = t.m[i][i];

                if (pivotsize < 0)
                    pivotsize = -pivotsize;

                for (j = i + 1; j < 4; j++) {
                    float tmp = t.m[j][i];

                    if (tmp < 0)
                        tmp = -tmp;

                    if (tmp > pivotsize) {
                        pivot = j;
                        pivotsize = tmp;
                    }
                }

                if (pivotsize == 0) {
                    return Mat4();
                }

                if (pivot != i) {
                    for (j = 0; j < 4; j++) {
                        float tmp;

                        tmp = t.m[i][j];
                        t.m[i][j] = t.m[pivot][j];
                        t.m[pivot][j] = tmp;

                        tmp = s.m[i][j];
                        s.m[i][j] = s.m[pivot][j];
                        s.m[pivot][j] = tmp;
                    }
                }

                for (j = i + 1; j < 4; j++) {
                    float f = t.m[j][i] / t.m[i][i];

                    for (k = 0; k < 4; k++) {
                        t.m[j][k] -= f * t.m[i][k];
                        s.m[j][k] -= f * s.m[i][k];
                    }
                }
            }

            for (i = 3; i >= 0; --i) {
                float f;

                if ((f = t.m[i][i]) == 0) {
                    return Mat4();
                }

                for (j = 0; j < 4; j++) {
                    t.m[i][j] /= f;
                    s.m[i][j] /= f;
                }

                for (j = 0; j < i; j++) {
                    f = t.m[j][i];

                    for (k = 0; k < 4; k++) {
                        t.m[j][k] -= f * t.m[i][k];
                        s.m[j][k] -= f * s.m[i][k];
                    }
                }
            }

            return s;
        }

        void print_matrix(){
            std::cout<<"the matrix is:"<<std::endl;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    std::cout<<m[i][j]<<" ";
                }
                std::cout<<"\n";
            }

        }
};

const Mat4 Mat4::Identity;

