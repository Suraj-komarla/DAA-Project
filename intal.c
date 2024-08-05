#include "intal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



typedef struct myintal
{

	int length;
	char s[0];
}myintal;

void strrev(char * str) {
	int j = 0, i = 0;
	while(str[j+1]) j++;
	while(i < j) {
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

void* intal_create(const char* str)
{
	myintal *intal=(myintal *)malloc(sizeof(myintal)+sizeof(char)*(strlen(str)+1));//+1 as strlen doesn't count null
	int i=0;
	if(str[0]=='\0')//empty string
	{
		intal->s[0]='\0';
		intal->length=1;
		return (void *)intal;
	}
	while(str[i]!='\0' && str[i]=='0')//removing leading zeroes
	{
			i++;
	}
	if(str[i]=='\0')//number is 0
	{
		intal->s[0]='0';
		intal->length=2; //0 and a null character
	}
	else
	{
		int j=0;
		for(j=0;str[i]!='\0';j++)
		{
			intal->s[j]=str[i];
			i++;
		}
		intal->length=j+1;//length is total characters plus a null character
	}
	intal->s[(intal->length)-1]='\0';// last character is null
	return (void *)intal;
} 

void intal_destroy(void* intal)
{
  if(intal != NULL)
	   free((myintal *)intal);
}

char* intal2str(void* intal)
{
  if(intal==NULL)
    return "NaN";
  return (((myintal *)intal)->s);
}

void* intal_increment(void* intal)
{
  	if(intal==NULL)
    	return intal;
	myintal * intall=(myintal *)intal;
	int i=(intall->length) -2;//last non-null character
	while(i>=0 && intall->s[i]=='9')//make all trailing 9's 0's
	{
		intall->s[i]='0';
		i--;
	}
	if(i==-1)//if every character was 9
	{
		myintal *intal2=(myintal *)malloc(sizeof(myintal)+sizeof(char)*((intall->length)+1));
		for(int j=1;j<=(intall->length)-1;j++)//all characters other than first character is made 0
		{
			intal2->s[j]='0';
		}
		intal2->s[0]='1';//first character is made 1
		intal2->length=(intall->length)+1;//new lenght is length+1
		intal2->s[intall->length]='\0';//last character is null
		free((void *)intall);
		return (void *)intal2;

	}
	else
	{
		intall->s[i]=(intall->s[i]) + 1; //change the first non-9 character to it's next digit
		return (void *)intall;
	}

}

void* intal_decrement(void* intal)
{
  	if(intal==NULL)
    	return intal;
	myintal * intall=(myintal *)intal;
	int i=(intall->length) -2;//last non null character
	if(intall->s[0]=='0')//if first character is 0, then 0 is the number, dont do anything
		return intall;
	if(intall->s[0]=='1' && intall->length==2)
	{
		intall->s[0]='0';
		return intall;
	}
	while(i>=0 && intall->s[i]=='0')//all trailing 0's made to 9
	{
		intall->s[i]='9';
		i--;
	}
	if(intall->s[i]=='1' && i==0)//if 1 was followed by zeroes
	{
		myintal *intal2=(myintal *)malloc(sizeof(myintal)+sizeof(char)*((intall->length)-1));//new length is lenght -1
		for(int j=0;j<=(intall->length)-3;j++)
		{
			intal2->s[j]='9';
		}
		intal2->s[(intall)->length-2]='\0';//last character is made null
		intal2->length=(intall->length)-1;//new length
		intal_destroy((void *)intall);
		return (void *)intal2;
	}
	else
	{
		intall->s[i]=(intall->s[i])-1;
		return intall;
	}
}

void* intal_add(void* intal1, void* intal2)
{

	if(intal2==NULL)
  	{
    	return intal2;
  	}
  	if(intal1==NULL)
  	{
    	return intal1;
  	}
  	
	myintal * intall1=(myintal *)intal1;
	myintal * intall2=(myintal *)intal2;
	int m=(intall1->length)-1;//no of characters in intal1 excluding null
	int n=(intall2->length)-1;//no of characters in intal2 excluding null
    if (m > n)//if length of intal1 is greater
    {
    	
 		myintal *intal3=(myintal *)malloc(sizeof(myintal)+sizeof(char)*((intall1->length)+2));//max length can be greater than intal1
    	int carry = 0;
    	int i;
    	int j;
    	int k;
    	for (i=m-1,j=n-1,k=0; j>=0; i--,j--,k++)//until intal2 gets exhausted
    	{
    		int sum=(intall1->s[i] -'0') + (intall2->s[j] -'0') + carry;
        	intal3->s[k]=(sum%10 + '0');
        	carry = sum/10;
    	}
    	while(i>=0)//add the remaining characters of intal1
    	{	
    		int sum=((intall1)->s[i]-'0') + carry;
    		intal3->s[k]=(sum%10 + '0');
    		carry=sum/10;
    		i--;
    		k++;
    	}
    	if (carry)
        	intal3->s[k++]=(carry + '0');
        intal3->s[k]='\0';
        strrev(intal3->s);
        intal3->length=k+1;
    	return ((void *)intal3);
    }

    else
    {
    	
 		myintal *intal3=(myintal *)malloc(sizeof(myintal)+sizeof(char)*((intall2->length)+2));
    	int carry = 0;
    	int i;
    	int j;
    	int k;
    	for (i=m-1,j=n-1,k=0; i>=0; i--,j--,k++)
    	{
    		int sum=(intall1->s[i] -'0') + ((intall2)->s[j] -'0') + carry;
        	(intal3)->s[k]=(sum%10 + '0');
        	carry = sum/10;
    	}
    	while(j>=0)
    	{	
    		int sum=(intall2->s[j]-'0') + carry;
    		(intal3)->s[k]=(sum%10 + '0');
    		carry=sum/10;
    		j--;
    		k++;
    	}
    	if (carry)
        	intal3->s[k++]=(carry + '0');
        intal3->s[k]='\0';
        strrev(intal3->s);
        intal3->length=k+1;
    	return ((void *)intal3);
    }
 }

void* intal_diff(void* intal1, void* intal2)
{
  	if(intal1==NULL)
    	return intal1;
  	if(intal2==NULL)
    	return intal2;
	myintal * intall1=(myintal *)intal1;
	myintal * intall2=(myintal *)intal2;
	int m=(intall1->length)-1;//no of characters in intal1 excluding null
	int n=(intall2->length)-1;//no of characters in intal2 excluding null
	int ans=intal_compare(intall1,intall2);
	if(ans==1)//intal1 is greater
	{
		myintal *intal3=(myintal *)malloc(sizeof(myintal)+sizeof(char)*(intall1->length));//temp
    	int carry = 0;
    	int i;
    	int j;
    	int k;
    	for (i=m-1,j=n-1,k=0;j>=0; i--,j--,k++)//until intal2 gets exhausted
    	{
    		int sub=(intall1->s[i] -'0') - (intall2->s[j] -'0' )- carry;
        	if (sub < 0)
        	{
            	sub = sub+10;
            	carry = 1;
        	}
        	else
            	carry = 0;
        	intal3->s[k]=(sub + '0');
    	}	
        while(i>=0)//for the remaining chracters of intal1
        {
        	if(intall1->s[i]=='0' && carry)
        	{
        		(intal3)->s[k]='9';
        		i--;
        		k++;
        		continue;
        	}
        	int sub=(intall1->s[i]-'0')-carry;
        	//if(i>0 || sub>0)
        	//{
        		(intal3)->s[k]=(sub + '0');
        	//}
        	i--;
        	k++;
        	carry=0;
        }
        (intal3)->s[k]='\0';
        strrev(intal3->s);
        int t=0;//find how many leading zeroes are there
        while(intal3->s[t]=='0')
        {
        	t++;
        }
        myintal *intal4=(myintal *)malloc(sizeof(myintal)+sizeof(char)*(intall1->length));//final
        strcpy(intal4->s,intal3->s+t);//copy the string 
        intal4->length=k+1-t;
        intal_destroy((void *)intal3);
    	return ((void *)intal4);

	}
	else if(ans==-1)
	{
		myintal *intal3=(myintal *)malloc(sizeof(myintal)+sizeof(char)*(intall2->length));
    	int carry = 0;
    	int i;
    	int j;
    	int k;
    	for (i=m-1,j=n-1,k=0;i>=0; i--,j--,k++)
    	{
    		int sub=(intall2->s[j] -'0') - (intall1->s[i] -'0') - carry;
        	if (sub < 0)
        	{
            	sub = sub+10;
            	carry = 1;
        	}
        	else
            	carry = 0;
        	(intal3)->s[k]=(sub + '0');

    	}	
        while(j>=0)
        {
        	if(intall2->s[j]=='0' && carry)
        	{
        		(intal3)->s[k]='9';
        		j--;
        		k++;
        		continue;
        	}
        	int sub=(intall2->s[j]-'0')-carry;
        	if(j>0 || sub>0)
        		(intal3)->s[k]=(sub + '0');
        	j--;
        	k++;
        	carry=0;
        }
        (intal3)->s[k]='\0';
        strrev(intal3->s);
        int t=0;
        while(intal3->s[t]=='0')
        {
        	t++;
        }
        myintal *intal4=(myintal *)malloc(sizeof(myintal)+sizeof(char)*(intall2->length));
        strcpy(intal4->s,intal3->s+t);
        intal4->length=k+1-t;
        intal_destroy((void *)intal3);
    	return ((void *)intal4);
	}
	else
	{
		myintal *intal3=(myintal *)malloc(sizeof(myintal)+sizeof(char)*2);
		intal3->s[0]='0';
		intal3->s[1]='\0';
		intal3->length=2;
		return (void *)intal3;

	}
 }

int intal_compare(void* intal1, void* intal2)
{
  	if(intal1==NULL)
    	return 0;
  	if(intal2==NULL)
    	return 0;
	myintal * intall1=(myintal *)intal1;
	myintal * intall2=(myintal *)intal2;
	int m=(intall1)->length;
	int n=(intall2)->length;

	if(m>n)
	{
		return 1;
	}
	else if(n>m)
		return -1;
	else
	{
		int ans=strcmp(intall1->s,intall2->s);
		if(ans==0)
			return 0;
		else if(ans>0)
			return 1;
		else
			return -1;
	}

}


myintal* remove_leading(myintal* intal3)
{
	int t=0;
    while(intal3->s[t]=='0')
    {
        t++;
    }
    myintal *intal4=(myintal *)malloc(sizeof(myintal)+sizeof(char)*((intal3->length)-t));
    strcpy(intal4->s,intal3->s+t);
    intal4->length=intal3->length-t;
    intal_destroy((void *)intal3);
    return ((void *)intal4);
}



void * intal_divide(void * intal1, void *intal2)
{
	if(intal1==NULL)
    	return intal1;
  	if(intal2==NULL)
    	return intal2;
	myintal *intall1=(myintal *)intal1;
	myintal *intall2=(myintal *)intal2;
	myintal * intal3;
    if(intall2->length==2 && intall2->s[0]=='0')
    {
    	intal3=(myintal *)malloc(sizeof(myintal));
    	intal3->length=0;
    	return intal3;
    }
   	if(intall2->length==2 && intall2->s[0]=='1')
   	{
   		intal3=(myintal *)malloc(sizeof(myintal)*sizeof(char)*(intall1->length));
   		for(int i=0;i<intall1->length;i++)
   		{
   			intal3->s[i]=intall1->s[i];
   		}
   		intal3->length=intall1->length;
   		return intal3;

   	}
   	if(intall1->length==2 && intall1->s[0]=='0')
   	{
   		intal3=(myintal *)malloc(sizeof(myintal)*sizeof(char)*(2));
   		intal3->s[0]='0';
   		intal3->s[1]='\0';
   		intal3->length=2;
   		return intal3;
   	}
   	if(intall1->length==2 && intall1->s[0]=='1')
   	{
   		intal3=(myintal *)malloc(sizeof(myintal)*sizeof(char)*(2));
   		intal3->s[0]='1';
   		intal3->s[1]='\0';
   		intal3->length=2;
   		return intal3;
   	}
   	int ans=intal_compare(intall1,intall2);
   	if(ans==-1)
   	{
   		intal3=(myintal *)malloc(sizeof(myintal)*sizeof(char)*(2));
   		intal3->s[0]='0';
   		intal3->s[1]='\0';
   		intal3->length=2;
   		return intal3;
   	}
   	else if(ans==0)
   	{
   		intal3=(myintal *)malloc(sizeof(myintal)*sizeof(char)*(2));
   		intal3->s[0]='1';
   		intal3->s[1]='\0';
   		intal3->length=2;
   		return intal3;
   	}
   	
   	intal3=(myintal *)malloc(sizeof(myintal)*sizeof(char)*intall1->length);
   	myintal *dividend=(myintal *)malloc(sizeof(myintal)*sizeof(char)*intall2->length);
   	dividend->length=intall2->length;
   	myintal *divisor=(myintal *)malloc(sizeof(myintal)*sizeof(char)*intall2->length);
   	divisor->length=intall2->length;
   	myintal *result=(myintal *)malloc(sizeof(myintal)*sizeof(char)*2);
   	result->s[0]='0';
   	result->s[1]='\0';
   	result->length=2;
   	
   	int m=intall1->length;
   	int n=intall2->length;
   	for(int i=0;i<n;i++)
   	{
   		divisor->s[i]=intall2->s[i];
   		dividend->s[i]=intall1->s[i];
   	}
        
	int t=n-1;
	int count=0;
	while(t<m)
	{
		int flag=0;
		if(intal_compare(dividend,divisor)>=0)
		{
			while(intal_compare(dividend,divisor)>=0)
			{
				
				dividend=(myintal *)intal_diff(dividend,divisor);
				result=(myintal *)intal_increment(result);
			}
			intal3->s[count++]=result->s[0];
			result=(myintal *)realloc(result,sizeof(myintal)*sizeof(char)*1);
			result->s[0]='0';
			flag=1;
		}
		else
		{	if(t==(m-1))
				break;
			dividend=(myintal*)realloc(dividend,sizeof(myintal)+sizeof(char)*((dividend->length)+1));
			dividend->length++;
			dividend->s[(dividend->length)-2]=intall1->s[t];
			dividend->s[dividend->length-1]='\0';
			dividend=remove_leading(dividend);
			t++;
		}
		if(!flag && intal_compare(dividend,divisor)==-1)
		{
			intal3->s[count++]='0';
		}
	}
	intal3->s[count]='\0';
	intal3->length=count+1;
	intal_destroy(result);
	intal_destroy(dividend);
	intal_destroy(divisor);
	return (void*)intal3;
}
void* intal_multiply(void* intal1, void* intal2)
{
	myintal *intall1=(myintal *)intal1;
	myintal *intall2=(myintal *)intal2;
	myintal *intal3;
	if(intall1->s[0]=='1' && intall1->length==2)
	{
		intal3=(myintal *)malloc(sizeof(myintal)+sizeof(char)*(intall2->length));
		strcpy(intal3->s,intall2->s);
		intal3->length=intall2->length;
		return intal3;
	}
	if(intall2->s[0]=='1' && intall2->length==2)
	{
		intal3=(myintal *)malloc(sizeof(myintal)+sizeof(char)*(intall2->length));
		strcpy(intal3->s,intall1->s);
		intal3->length=intall1->length;
		return intal3;
	}
	if(intal3->s[0]=='0' || intall2->s[0]=='0')
	{
		intal3=(myintal *)malloc(sizeof(myintal)+sizeof(char)*2);
		intal3->s[0]='0';
		intal3->s[1]='\0';
		intal3->length=2;
		return intal3;
	}
	int ans=intal_compare(intal1,intal2);
    if(ans==-1)
    {
		intall1=intal1;
		intall2=intal2;
	}
	int n=intall1->length -1 + intall2->length;
	int r=n-2;
	intal3=(myintal *)malloc(sizeof(myintal)*sizeof(char)*(n));
	intal3->length=n;
	intal3->s[intal3->length-1]='\0';
	int tmp;
	for(int i=0;i<n-1;i++)
	{
		intal3->s[i]='0';
	}
	for(int i=intall2->length-2;i>=0;i--)
	{
		int offset=0;
        int carry=0;
        for(int j=intall1->length-2;j>=0;j--)
        {
            tmp=((intall1->s[j] - '0') * (intall2->s[i]-'0') + carry + intal3->s[r-offset]-'0');
            carry=tmp/10;
            intal3->s[r-offset]=tmp%10 + '0';
            offset++;
        }
        if(carry!=0)
        {
            intal3->s[r-offset]=carry+'0';
       	}
        r--;
	}
	intal3=remove_leading(intal3);
	return intal3;
}

myintal * power(myintal * intal1, myintal * intal2);
myintal *temptwo;
void* intal_pow(void* intal1, void* intal2)
{
  
  temptwo=(myintal *)malloc(sizeof(myintal)+sizeof(char)*2);
  temptwo->s[0]='2';
  temptwo->s[1]='\0';
  temptwo->length=2;
  if(intal1==NULL)
    return intal1;
  if(intal2==NULL)
    return intal2;
  myintal * intall1=(myintal *)intal1;
  myintal * intall2=(myintal *)intal2;
  if(intall1->s[0]=='0')
  {
	    myintal * intal3=(myintal *)malloc(sizeof(myintal)+sizeof(char)*2);
		intal3->s[0]='1';
		intal3->s[1]='\0';
		intal3->length=2;
		return (void *)intal3;
  }
	else
		return (void *)power(intall1,intall2);
}

myintal * power(myintal * intal1, myintal * intal2)
{
	if(intal2->s[0]=='1' && intal2->length==2)
	{

		myintal * intal3=(myintal *)malloc(sizeof(myintal)+sizeof(char)*intal1->length);
		intal3->length=intal1->length;
		strcpy(intal3->s,intal1->s);
		printf("%s\n",intal3->s);
		return (void *)intal3;
	}
	if(intal2->s[0]=='0')
	{
		myintal * intal3=(myintal *)malloc(sizeof(myintal)+sizeof(char)*2);
		intal3->s[0]='1';
		intal3->s[1]='\0';
		intal3->length=2;
		return (void *)intal3;
	}
	void * bytwo=(myintal *)intal_divide(intal2,temptwo);
	printf("%s\n",((myintal *)bytwo)->s);
    myintal *ans = power(intal1,bytwo);
    ans=intal_multiply(ans,ans);
    if((intal2->s[0]-'0')%2==1)
    	ans=intal_multiply(ans,intal1);
    return ans;   
}


