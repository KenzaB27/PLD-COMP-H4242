int main()
{
    int a = 0;
    int b = 56; 
    for (int i = 10; i > 0; i--)
    {
        while (a <= 12)
        {
            a = a + 3 *b;
            
        }
        if (a > 0)
        {
            a = -100 ; 
        }
        a = a + 6;
    }
    return a;
}