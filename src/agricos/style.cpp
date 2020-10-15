#include "style.h"
/*


  /$$$$$$                      /$$            /$$$$$$   /$$$$$$ 
 /$$__  $$                    |__/           /$$__  $$ /$$__  $$
| $$  \ $$  /$$$$$$   /$$$$$$  /$$  /$$$$$$$| $$  \ $$| $$  \__/
| $$$$$$$$ /$$__  $$ /$$__  $$| $$ /$$_____/| $$  | $$|  $$$$$$ 
| $$__  $$| $$  \ $$| $$  \__/| $$| $$      | $$  | $$ \____  $$
| $$  | $$| $$  | $$| $$      | $$| $$      | $$  | $$ /$$  \ $$
| $$  | $$|  $$$$$$$| $$      | $$|  $$$$$$$|  $$$$$$/|  $$$$$$/
|__/  |__/ \____  $$|__/      |__/ \_______/ \______/  \______/ 
           /$$  \ $$                                            
          |  $$$$$$/                                            
           \______/                                             

*/

void AgricosStyle_PrintAsciiLogo(Print &cout)
{
    cout.println("\033[1m \033[93m");
    cout.println(F("  /$$$$$$                      /$$            /$$$$$$   /$$$$$$ "));
    cout.println(F(" /$$__  $$                    |__/           /$$__  $$ /$$__  $$"));
    cout.println(F("| $$  \\ $$  /$$$$$$   /$$$$$$  /$$  /$$$$$$$| $$  \\ $$| $$  \\__/"));
    cout.println(F("| $$$$$$$$ /$$__  $$ /$$__  $$| $$ /$$_____/| $$  | $$|  $$$$$$ "));
    cout.println(F("| $$__  $$| $$  \\ $$| $$  \\__/| $$| $$      | $$  | $$ \\____  $$"));
    cout.println(F("| $$  | $$| $$  | $$| $$      | $$| $$      | $$  | $$ /$$  \\ $$"));
    cout.println(F("| $$  | $$|  $$$$$$$| $$      | $$|  $$$$$$$|  $$$$$$/|  $$$$$$/"));
    cout.println(F("|__/  |__/ \\____  $$|__/      |__/ \\_______/ \\______/  \\______/ "));
    cout.println(F("           /$$  \\ $$                                            "));
    cout.println(F("          |  $$$$$$/                                            "));
    cout.println(F("           \\______/                                             "));
    cout.println("\033[0m");
}