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
        
        int j;
        j = 0;
        while (j < 10) {
            if ((i==9) && (j==5))
                return suivant;
            j++;
        }
              
    }

    return suivant;
}
