int main ()
{
    int operation = 7; 
    int a,b,c ; 
    a= 6 ; 
    b = 9; 
    c = 1; 
    if (operation == 0)
        return a+b; 
    else if (operation == 1)
        return a - b;
    else if (operation ==2)
        return a*b ;
    else if (operation ==3)
        return a/b; 
    else if (operation == 4)
        return a%b;
    else if (operation == 5)
        return (a&b)|a^c;
    else if (operation == 6)
        return a << b; 
    else if (operation == 7)
        return a >> b; 
    else 
        return a++;
}