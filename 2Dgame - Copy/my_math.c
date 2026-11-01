double my_cos(double a){
    double term=1.0f;
    double result=1.0f;
    int n=1;
    while(n<10){
        term = -term*a*a/((2*n-1)*(2*n));
        result = result+term;
        n=n+1;
    }
    return result;    
}
double my_sin(double a){
    double term=a;
    double result=a;
    int n=1;
    while(n<10){
        term = -term*a*a/((2*n)*(2*n+1));
        result=result+term;
        n=n+1;
    }
    return result;
}
double my_sqrt(double a){
    double currentnum = a;
    double mainguess;
    mainguess = (double)(currentnum + a / currentnum) / 2.0f;
    return mainguess;
}






