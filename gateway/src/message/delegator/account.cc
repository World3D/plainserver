#include "common/application/net/packet/gateway_tologin/resultauth.h"
#include "common/base/log.h"
#include "db/user.h"
#include "message/delegator/account.h"

using namespace message::delegator;
using namespace ps_common_net;
using namespace ps_common_application::net::packet;

void account::auth(login_togateway::AskAuth *message,
                   connection::Base *connection) {
  __ENTER_FUNCTION
    db::user_t userinfo;
    db::user::get_fullinfo(message->getaccount(), userinfo);
    uint8_t result = 1;
    if (strcmp(userinfo.name, message->getpassword())) {
      result = 0;
    }
    gateway_tologin::ResultAuth resultmessage;
    resultmessage.setresult(result);
    resultmessage.setaccount(message->getaccount());
    resultmessage.setpassword(message->getpassword());
    connection->sendpacket(&resultmessage);
    SLOW_LOG("gateway", 
             "[message.delegator] (account::auth) success!"
             " account: %s, result: %d", 
             message->getaccount(), 
             result);    
  __LEAVE_FUNCTION
}
