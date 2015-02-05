
float get_specular_factor(Light_source light_source,Vec3 normal_at_hit, Vec3 closest_hit_point, Vec3 viewing_direction){
    Vec3 light_direction = light_source.position - closest_hit_point;
    light_direction.normalize();
    Vec3 reflection_direction = (normal_at_hit * (normal_at_hit.dot(light_direction))) * 2.0 - light_direction;
    reflection_direction.normalize();
    float cos_theta = reflection_direction.dot(viewing_direction);
    if(cos_theta < 0) cos_theta = 0;
    return pow(cos_theta,30);
}

float get_diffused_factor(Light_source light_source, Vec3 normal, Vec3 closest_hit_point){
    Vec3 light_direction = light_source.position - closest_hit_point;
    light_direction.normalize();
    float diffused_factor = light_direction.dot(normal);
    if(diffused_factor<0) diffused_factor = 0;
    return diffused_factor;
}

Vec3 find_phong_illumination(Object* object, vector<Object*> objects, Vec3 closest_hit_point, Vec3 viewing_direction, Vec3 normal_at_hit, vector<Light_source> light_sources){

    Vec3 phong_color = object->color;

    for(int i=0; i<light_sources.size(); i++){
        bool is_in_shadow = false;
        float t = 0;
        Light_source light_source = light_sources[i];
        Vec3 shadow_ray_direction = light_source.position - closest_hit_point;
        Ray shadow_ray(closest_hit_point, shadow_ray_direction);

        for(int j=0; j<objects.size(); j++){
            if(object->intersect(shadow_ray, t)){
                is_in_shadow = true;
                break;
            }
        }

        if(is_in_shadow)
            continue;
        else {
            float diffused_factor = get_diffused_factor(light_source,normal_at_hit, closest_hit_point);
            Vec3 diffused_contribution = Vec3(1,1,1) * diffused_factor;
            Vec3 diffused_color_component = (phong_color + diffused_contribution)/2;
            phong_color = diffused_color_component;
        }
    }

    return phong_color;
}
