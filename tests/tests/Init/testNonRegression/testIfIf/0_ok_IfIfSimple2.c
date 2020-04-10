int main()
{
    int a = 12;

    if (a == 12)
    {
        a = 5;
        if (a == 5)
        {
            a = 12;
            if (a ==12)
            {
                a=45; 
            }
        }
        else if (a ==45)
        {
            a = 2;
        }
        else {
            a= 69;
        }
    }
    a = a + 6;

    return a;
}