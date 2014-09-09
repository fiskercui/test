
#ifndef __PLAYER_MessageBoxServiceMac_h
#define __PLAYER_MessageBoxServiceMac_h

#include "PlayerMacros.h"
#include "PlayerMessageBoxServiceProtocol.h"
#include <vector>
#include <string>

PLAYER_NS_BEGIN

class PlayerMessageBoxServiceMac : public PlayerMessageBoxServiceProtocol
{
public:
    virtual int showMessageBox(const std::string &title,
                               const std::string &message,
                               int buttonsType = BUTTONS_OK);
    
private:
    std::vector<std::string> getTitles(int buttons);
    
};

PLAYER_NS_END

#endif // __PLAYER_MessageBoxServiceMac_h
