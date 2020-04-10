int main()
{
    int n = 10; 
    int nbr1 = 0 ;
    int nbr2 = 1 ;
    int  suivant, i;

    for (i = 0; i < n; i++)
    {
        if (i <= 1)
            suivant = i;
        else
        {
            suivant = nbr1 + nbr2;
            nbr1 = nbr2;
            nbr2 = suivant;
        }
    }

    return suivant;
}