
#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"
#include <EEPROM.h>
#include <RobotIRremote.h>
#include <RobotIRremoteInt.h>
#include <RobotIRremoteTools.h>
#include "IRremote.h"
#include <iostream>
#include <conio.h>
#include <string.h>
using namespace std;

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)

  {

 
  case 0xFF22DD: Serial.println(" LEFT");    break;
  case 0xFF02FD: Serial.println(" -OK-");    break;
  case 0xFFC23D: Serial.println(" RIGHT");   break;
  case 0xFF6897: Serial.println(" 1");    break;
  case 0xFF9867: Serial.println(" 2");    break;
  case 0xFFB04F: Serial.println(" 3");    break;
  case 0xFF30CF: Serial.println(" 4");    break;
  case 0xFF18E7: Serial.println(" 5");    break;
  case 0xFF7A85: Serial.println(" 6");    break;
  case 0xFF10EF: Serial.println(" 7");    break;
  case 0xFF38C7: Serial.println(" 8");    break;
  case 0xFF5AA5: Serial.println(" 9");    break;
  case 0xFF4AB5: Serial.println(" 0");    break;

  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat


} 

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("HELLO");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
}
unsigned int difference ( unsigned int &start_time, unsigned int &end_time )
{
    end_time = clock();
    return ( ( end_time - start_time )  /1000 );
}


int main ()
{
    
    string account = "";
    string password = "";
    bool loginSuccess = false;
    unsigned int start_time = clock();
    unsigned int end_time;
    s2:
    cout << "\nHELLO\n";                            //system start with the world "HELLO"
    

    do{
      cout << "Acc.No:  ";
      while ( difference ( start_time, end_time) < 60 )
    {
        cout<< difference ( start_time, end_time) << endl;         //wait for 60 seconds after that it will exit the main() and start again .
        cin >> account;
    }
    s3:
      cout << "PassCO:  ";
      while ( difference ( start_time, end_time) < 60 )
    {
        cout<< difference ( start_time, end_time) << endl;         //wait for 60 seconds after that it will exit the main() and start again .
        cin >> password;
    }

//////////////////////////////
      

      if(account == "100000" && password == "1000")
      {
        cout << "\n Welcome Mr./Ms. A";
        loginSuccess = true;
        cout << "\n\t*     1. Check Balance             *";
        cout << "\n\t*     2. Withdraw                  *";
        cout << "\n\t*     3. Deposit                   *";
        cout << "\n\t*     4. Exit                      *";
        int balance=1323;
        int withdraw;
        int deposit;
        s:
        cout << "\nEnter Number: ";
        cin >> choice;
        if (choice==1)
        {
            cout <<"\n/mr./Ms. A: \n" << balance;         //display balance along with user name
            
            goto s;
        }
        else if (choice==2)
        {
            cout << "\amt: ";
            cin >> withdraw;
            if (withdraw>balance && withdraw < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                cout << "\amt: " << balance
                goto s;
            }
            else
            {
            balance=balance-withdraw;    
            cout << "\namt: \n" << balance;   
            goto s;
            }
        }
        else if (choice==3)
        {
            cout << "\nEnter amt: ";
            cin >> deposit;
            if (deposit < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                goto s;
            }
            else
            {
              balance=balance+deposit;
              cout << "\nYour current balance is: \n" << balance;   
              goto s;
            }
            
        }
        else if (choice==4)
        {
            cout << "\nTHANK YOU!";
        }
    }

    if(account == "100001" && password == "1001")
      {
        cout << "\n Welcome Mr./Ms. B";
        loginSuccess = true;
    cout << "\n\t*     1. Check Balance             *";
    cout << "\n\t*     2. Withdraw                  *";
    cout << "\n\t*     3. Deposit                   *";
    cout << "\n\t*     4. Exit                      *";
        int balance=132663;
        int withdraw;
        int deposit;
        s:
        cout << "\nEnter Number: ";
        cin >> choice;
        if (choice==1)
        {
            cout <<"\n/mr./Ms. B: \n" << balance;         //display balance along with user name
            goto s;
        }
        else if (choice==2)
        {
            cout << "\amt: ";
            cin >> withdraw;
            if (withdraw>balance && withdraw < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                cout << "\amt: " << balance
                goto s;
            }
            else
            {
            balance=balance-withdraw;    
            cout << "\namt: \n" << balance;   
            goto s;
            }
        }
        else if (choice==3)
        {
            cout << "\nEnter amt: ";
            cin >> deposit;
            if (deposit < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                goto s;
            }
            else
            {
              balance=balance+deposit;
              cout << "\nYour current balance is: \n" << balance;   
              goto s;
            }
            
        }

  else if(account == "100002" && password == "102")
      {
        cout << "\n Welcome Mr./Ms. C";
        loginSuccess = true;
    cout << "\n\t*     1. Check Balance             *";
    cout << "\n\t*     2. Withdraw                  *";
    cout << "\n\t*     3. Deposit                   *";
    cout << "\n\t*     4. Exit                      *";
        int balance=1323;
        int withdraw;
        int deposit;
        s:
        cout << "\nEnter Number: ";
        cin >> choice;
        if (choice==1)
        {
            cout <<"\n/mr./Ms. C: \n" << balance;         //display balance along with user name
            goto s;
        }
        else if (choice==2)
        {
            cout << "\amt: ";
            cin >> withdraw;
            if (withdraw>balance && withdraw < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                cout << "\amt: " << balance
                goto s;
            }
            else
            {
            balance=balance-withdraw;    
            cout << "\namt: \n" << balance;   
            goto s;
            }
        }
        else if (choice==3)
        {
            cout << "\nEnter amt: ";
            cin >> deposit;
            if (deposit < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                goto s;
            }
            else
            {
              balance=balance+deposit;
              cout << "\nYour current balance is: \n" << balance;   
              goto s;
            }
        }
        else if (choice==4)
        {
            cout << "\nTHANK YOU!";
        }
    }

    else if(account == "100003" && password == "1003")
      {
        cout << "\n Welcome Mr./Ms. D";
        loginSuccess = true;
    cout << "\n\t*     1. Check Balance             *";
    cout << "\n\t*     2. Withdraw                  *";
    cout << "\n\t*     3. Deposit                   *";
    cout << "\n\t*     4. Exit                      *";
        int balance=433;
        int withdraw;
        int deposit;
        s:
        cout << "\nEnter Number: ";
        cin >> choice;
        if (choice==1)
        {
            cout <<"\n/mr./Ms. D: \n" << balance;         //display balance along with user name
            goto s;
        }
        else if (choice==2)
        {
            cout << "\amt: ";
            cin >> withdraw;
            if (withdraw>balance && withdraw < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                cout << "\amt: " << balance
                goto s;
            }
            else
            {
            balance=balance-withdraw;    
            cout << "\namt: \n" << balance;   
            goto s;
            }
        }
        else if (choice==3)
        {
            cout << "\nEnter amt: ";
            cin >> deposit;
            if (deposit < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                goto s;
            }
            else
            {
              balance=balance+deposit;
              cout << "\nYour current balance is: \n" << balance;   
              goto s;
            }
            
        }
        else if (choice==4)
        {
            cout << "\nTHANK YOU!";
        }
    }

    else if(account == "10004" && password == "1004")
      {
        cout << "\n Welcome Mr./Ms. E";
        loginSuccess = true;
    cout << "\n\t*     1. Check Balance             *";
    cout << "\n\t*     2. Withdraw                  *";
    cout << "\n\t*     3. Deposit                   *";
    cout << "\n\t*     4. Exit                      *";
        int balance=1323;
        int withdraw;
        int deposit;
        s:
        cout << "\nEnter Number: ";
        cin >> choice;
        if (choice==1)
        {
            cout <<"\n/mr./Ms. E: \n" << balance;         //display balance along with user name
            goto s;
        }
        else if (choice==2)
        {
            cout << "\amt: ";
            cin >> withdraw;
            if (withdraw>balance && withdraw < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                cout << "\amt: " << balance
                goto s;
            }
            else
            {
            balance=balance-withdraw;    
            cout << "\namt: \n" << balance;   
            goto s;
            }
        }
        else if (choice==3)
        {
            cout << "\nEnter amt: ";
            cin >> deposit;
            if (deposit < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                goto s;
            }
            else
            {
              balance=balance+deposit;
              cout << "\nYour current balance is: \n" << balance;   
              goto s;
            }
            
        }
        else if (choice==4)
        {
            cout << "\nTHANK YOU!";
        }
    }

   else if(account == "100005" && password == "1005")
      {
        cout << "\n Welcome Mr./Ms. F";
        loginSuccess = true;
    cout << "\n\t*     1. Check Balance             *";
    cout << "\n\t*     2. Withdraw                  *";
    cout << "\n\t*     3. Deposit                   *";
    cout << "\n\t*     4. Exit                      *";
        int balance=8313;
        int withdraw;
        int deposit;
        s:
        cout << "\nEnter Number: ";
        cin >> choice;
        if (choice==1)
        {
            cout <<"\n/mr./Ms. F: \n" << balance;         //display balance along with user name
            goto s;
        }
        else if (choice==2)
        {
            cout << "\amt: ";
            cin >> withdraw;
            if (withdraw>balance && withdraw < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                cout << "\amt: " << balance
                goto s;
            }
            else
            {
            balance=balance-withdraw;    
            cout << "\namt: \n" << balance;   
            goto s;
            }
        }
        else if (choice==3)
        {
            cout << "\nEnter amt: ";
            cin >> deposit;
            if (deposit < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                goto s;
            }
            else
            {
              balance=balance+deposit;
              cout << "\nYour current balance is: \n" << balance;   
              goto s;
            }
            
        }
        else if (choice==4)
        {
            cout << "\nTHANK YOU!";
        }
    }

    else if(account == "100006" && password == "1006")
      {
        cout << "\n Welcome Mr./Ms. G";
        loginSuccess = true;
    cout << "\n\t*     1. Check Balance             *";
    cout << "\n\t*     2. Withdraw                  *";
    cout << "\n\t*     3. Deposit                   *";
    cout << "\n\t*     4. Exit                      *";
        int balance=1323;
        int withdraw;
        int deposit;
        s:
        cout << "\nEnter Number: ";
        cin >> choice;
        if (choice==1)
        {
            cout <<"\n/mr./Ms. G: \n" << balance;         //display balance along with user name
            goto s;
        }
        else if (choice==2)
        {
            cout << "\amt: ";
            cin >> withdraw;
            if (withdraw>balance && withdraw < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                cout << "\amt: " << balance
                goto s;
            }
            else
            {
            balance=balance-withdraw;    
            cout << "\namt: \n" << balance;   
            goto s;
            }
        }
        else if (choice==3)
        {
            cout << "\nEnter amt: ";
            cin >> deposit;
            if (deposit < 0)
            {
                cout << "\nERROR\n";
                delay(2000);                                  // 2 sec. delay
                goto s;
            }
            else
            {
              balance=balance+deposit;
              cout << "\nYour current balance is: \n" << balance;   
              goto s;
            }
            
        }
        else if (choice==4)
        {
            cout << "\nTHANK YOU!";
        }
      }

        
        else if (choice==4)
        {
            cout << "\nTHANK YOU!";
        }
    }
    
    else                                                        // allow the user to enter password one ore time 
    { 
      count=0;
      if (count < 2)
      {
        cout << "\nInvalid pin!";
        delay(2000);                                             // 2 sec. delay
        goto s3;
      }
      else
      {
        goto s2;
        }
      count++;
    }

    
    return 0;
    getch();
      }
    }

     