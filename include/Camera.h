class Camera
{
    public:
        Mat4 world_to_camera_matrix,camera_to_world_matrix;
        float fov_angle, fov_angle_in_degree, fov_range;
        Camera(float fov=90, Mat4 world_to_camera_matrix = Mat4::Identity){
            fov_angle = fov;
            this->world_to_camera_matrix = world_to_camera_matrix;
            camera_to_world_matrix = world_to_camera_matrix.get_inverse();
            fov_angle_in_degree = (fov_angle * M_PI)/180;
            fov_range = tan(fov_angle_in_degree/2);
        }

        void rotate_x(float angle){
            world_to_camera_matrix.rotateX(angle);
            camera_to_world_matrix = world_to_camera_matrix.get_inverse();
        }

        void rotate_y(float angle){
            world_to_camera_matrix.rotateY(angle);
            camera_to_world_matrix = world_to_camera_matrix.get_inverse();
        }

        void rotate_z(float angle){
            world_to_camera_matrix.rotateZ(angle);
            camera_to_world_matrix = world_to_camera_matrix.get_inverse();
        }
};

