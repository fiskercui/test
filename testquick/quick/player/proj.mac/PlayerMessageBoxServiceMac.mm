
#include "PlayerMessageBoxServiceMac.h"

PLAYER_NS_BEGIN


int PlayerMessageBoxServiceMac::showMessageBox(const std::string &title,
                                         const std::string &message,
                                         int buttonsType)
{
    NSAlert *alert = [[NSAlert alloc] init];

    std::vector<std::string> titles = getTitles(buttonsType);
    for (std::string& title : titles)
    {
        [alert addButtonWithTitle:[NSString stringWithUTF8String:title.c_str()]];
    }
    
    [alert setMessageText:[NSString stringWithUTF8String:title.c_str()]];
    [alert setInformativeText:[NSString stringWithUTF8String:message.c_str()]];
    [alert setAlertStyle:NSWarningAlertStyle];
    
    int buttonId = (int)[alert runModal] - NSAlertFirstButtonReturn;
    return buttonId;
}

std::vector<std::string> PlayerMessageBoxServiceMac::getTitles(int buttons)
{
    std::vector<std::string> titles;
    
    switch (buttons) {
        case BUTTONS_OK:
            titles.push_back("OK");
            break;
            
        case BUTTONS_OK_CANCEL:
            titles.push_back("OK");
            titles.push_back("Cancel");
            break;
            
        case BUTTONS_YES_NO:
            titles.push_back("Yes");
            titles.push_back("No");
            break;
            
        case BUTTONS_YES_NO_CANCEL:
            titles.push_back("Yes");
            titles.push_back("No");
            titles.push_back("Cancel");
            break;

        default:
            break;
    }
    
    return titles;
}

PLAYER_NS_END