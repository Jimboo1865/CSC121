def catalanSequence():
    n=0
    C=1
    while (C<=1000000):
        print(C)
        C*=((4*n)+2)/(n+2)
        n+=1
    print('Done')
catalanSequence()