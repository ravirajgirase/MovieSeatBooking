#include<iostream>
#include <string>
#include <cstring>
#include <iterator>
#include <algorithm>
using namespace std;
int theater[3][3][9] = {
						{
							{0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,2,2,2},
							{2,0,0,0,0,0,0,2,2}
						},
						{
							{0,0,0,0,0,0,0,2,2},
							{2,0,0,0,0,0,2,2,2},
							{0,0,0,0,0,0,0,2,2}
						},
						{
							{0,0,0,0,0,0,0,2,2},
							{0,0,0,0,0,0,0,0,2},
							{0,0,0,0,0,0,0,0,0}
						}
					   };//0-Available,1-Booked,2-Not Available
int price[3][3] = {{0,0,320},{1,1,280},{2,2,240}};//{from_row,to_row,price}both inclusive
char status[3] = {'A','B','N'};

void show_seats_availibility(int);
bool check_seat_availibility(int, char*);
bool book_seats(int, char*);
void total_sales();
int main(){
	int shno=0,choice;
	char cseats[10],bseats[10];
	int showlen = int((sizeof(theater)/ sizeof(theater[shno])));
	while(true){
		cout<<"0.Exit\n1.Show Availability\n2.Check Availibility\n3.Book Ticket\n4.Total Sales\nEnter your choice:";
		cin>>choice;
		switch(choice){
			case 1:
				cout<<"Enter Show number:";
    			cin>>shno;
    			show_seats_availibility(shno-1);
				break;
			case 2:
				cout<<"Enter Show number:";
    			cin>>shno;
	            cout<<"Enter Seat number:";
	            cin>>cseats;
    			check_seat_availibility(shno-1, cseats);
				break;
			case 3:
				cout<<"Enter Show number:";
    			cin>>shno;
	            cout<<"Enter Seat number:";
	            cin>>bseats;
    			if(!book_seats(shno-1, bseats)){
    				cout<<"wrong seats";	
				}
				break;
			case 4:
				total_sales();
				break;
			case 0:
				return 0;
				break;
			default: cout<<"Invalid choice:"<<endl;
				break;
		}
	cout<<endl;
    }
	return 0;
}

void show_seats_availibility(int shno){
    cout<<"Seates available\n";
	for(int i=0;i<3;i++){
		for(int j=0;j<9;j++){
			cout<<char('A'+i)<<(j+1)<<'('<<status[theater[shno][i][j]]<<')'<<'\t';
		}
		cout<<endl;
    }
}

bool check_seat_availibility(int shno, char cseats[10]){
    bool status=true;
    char* ptr=strtok(cseats,",");
//    cout<<ptr;
    while(ptr!=NULL){
    	int row, col, rowlen=0, collen=0;
    	row = (int)ptr[0]-65;
    	col = (int)ptr[1]-49;
    	cout<<row<<col<<endl;
    	rowlen = int((sizeof(theater[shno])/ sizeof(theater[shno][0])));
		collen = int((sizeof(theater[shno][row])/ sizeof(theater[shno][row][0])));
		if(!(0<=row and row<rowlen)){
            return false;
		}
		if(!(0<=col and col<collen)){
            return false;  
		}
    	if(theater[shno][row][col]==0){
    		cout<<ptr<<"\t Available"<<endl;
		}else if(theater[shno][row][col]==1){
    		cout<<ptr<<"\t Booked"<<endl;
    		status = false;
		}else if(theater[shno][row][col]==2){
    		cout<<ptr<<"\t Not Available"<<endl;
    		status = false;
		}
    	ptr = strtok(NULL, ",");
	}
	return status;
}

bool book_seats(int shno, char bseats[10]){
    bool status=true;
    char* ptr=strtok(bseats,",");
    float total_price = 0.0;
    while(ptr!=NULL){
    	int row, col, rowlen=0, collen=0;
    	row = (int)ptr[0]-65;
    	col = (int)ptr[1]-49;
    	rowlen = int((sizeof(theater[shno])/ sizeof(theater[shno][0])));
		collen = int((sizeof(theater[shno][row])/ sizeof(theater[shno][row][0])));
		if(!(0<=row and row<rowlen)){
            return false;
		}
		if(!(0<=col and col<collen)){
            return false;  
		}
		if(theater[shno][row][col]==1 || theater[shno][row][col]==2){
			return false;
		}

			theater[shno][row][col] = 1;
			for(int i=0;i<int(sizeof(price)/sizeof(price[0]));i++){
			    if(price[i][0]<=row and row<=price[i][1]){
			        total_price+=price[i][2];
			    }
			}
		
		ptr = strtok(NULL, ",");
    }
    cout<<"Successfully Booked Show"<<endl;
    cout<<"Subtotal="<<total_price<<endl;
    float stax = total_price*0.14;
    cout<<"Service Tax @14%="<<stax<<endl;
    float sbc = total_price*0.005;
    cout<<"Swachh Bharat Cess @0.5%="<<sbc<<endl;
    float kkc = total_price*0.005;
    cout<<"Krishi Kalyan Cess @0.5%="<<kkc<<endl;
    cout<<"Total="<<total_price+stax+sbc+kkc<<endl;
//    show_seats_availibility(shno);
    return true;
}

void total_sales(){
	int total_sales = 0;
	for(int i=0;i<int(sizeof(price)/sizeof(price[0]));i++){
		    if(price[i][0]<=3 and 3<=price[i][1]){
		        total_sales+=price[i][2];
		    }
		}
	cout<<"Revenue="<<total_sales<<endl;
    float stax = total_sales*0.14;
    cout<<"Service Tax @14%="<<stax<<endl;
    float sbc = total_sales*0.005;
    cout<<"Swachh Bharat Cess @0.5%="<<sbc<<endl;
    float kkc = total_sales*0.005;
    cout<<"Krishi Kalyan Cess @0.5%="<<kkc<<endl;
    cout<<"Total="<<total_sales+stax+sbc+kkc<<endl;
}