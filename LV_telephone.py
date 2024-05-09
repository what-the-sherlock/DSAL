def insertlinear(ht,n):
    key=int(input("enter element="))
    loc=key%n
    if(ht[loc]==-1):
        ht[loc]=key
    else:
        cnt=0
        while(ht[loc]!=-1):
            loc=(loc+1)%n
            cnt=cnt+1
            if(cnt==n):
                print("overflow") 
                break
        ht[loc]=key        
    print(ht)

def linearsearch(ht,n):
        
    key=int(input("enter element="))
    loc=key%n
    if(ht[loc]==key):
       print("element fount at index ",loc)
    else:
        while(ht[loc]!=-1):
            loc=(loc+1)%10
            if(ht[loc]==key):
                print("element found at index ",loc)
                return True
    print("not found")        
          
def insertquad(ht,n):
    key=int(input("enter element="))
    loc=key%n
    if(ht[loc]==-1):
        ht[loc]=key
    else:
        cnt=0
        step=1
        while(ht[loc]!=-1):
            loc=(loc+step**2)%n
            cnt=cnt+1
            step=step+1
            if(cnt==n):
                print("overflow")
                break
        ht[loc]=key        
    print(ht)

def searchquad(ht,n):
        
    key=int(input("enter element="))
    loc=key%n
    if(ht[loc]==key):
       print("element fount at index ",loc)
    else:
        step=1
        while(ht[loc]!=-1):
            loc=(loc+step**2)%10
            step=step+1
            if(ht[loc]==key):
                print("element found at index ",loc)
                return True
    print("not found")        

def main():
    n=int(input("enter size of hash table="))
    ht=[]
    for i in range(n):
        ht.append(-1)
    
    while(1):
        print("1.insert linear\n")
        print("2.search key")
        print("3.insert quadratic")
        print("4.search quadratic")
        print("5.exit")
        ch=int(input("enter your choice="))

        match ch:
            case 1:
                insertlinear(ht,n)
            case  2:
                linearsearch(ht,n)    
            case 3:
                insertquad(ht,n)
            case 4:
                searchquad(ht,n)
            case 5 :
                exit(0)        
                
main()