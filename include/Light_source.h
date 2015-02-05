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
