
bool solve_quadric(float a, float b, float c, float &x0, float &x1){
    float discriminat = b*b - 4*a*c;
    if(discriminat<0) false;
    else if (discriminat == 0) x0 = x1 = - 0.5 * b / a;
    else {
        x0 = (-b + sqrt(discriminat))/(2*a);
        x1 = (-b - sqrt(discriminat))/(2*a);
    }

    if (x0 > x1) std::swap(x0, x1);
    return true;
}
