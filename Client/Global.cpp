#include "Visual_interface.h"

int sock_global = 0;
int pos_global = static_cast<int>(Scene::Start_Sc);
std::string id_global = "20240001";
std::string name_global = "";
std::string passwd_global="";
std::string areas_aid = "";
std::string areas_name = "";
std::string areas_introduction = "";
std::string areas_remaining_tickets = "";
std::string areas_tickets_total = "";
std::vector<std::string> records_global;
bool judgment_err_ = false;
const char* start_ = "\
-----------------------------------------------------------------------\n\
|        Electronic ticket system for tourist attractions             |\n\
|                                                                     |\n\
|                                                                     |\n\
|                           1.Login                                   |\n\
|                                                                     |\n\
|                           2.Register                                |\n\
|                                                                     |\n\
|                           3.Quit                                    |\n\
|                                                                     |\n\
|                                                                     |\n\
|                                                                     |\n\
-----------------------------------------------------------------------\n\
 ";

const char* login_ = "\
-----------------------------------------------------------------------\n\
|                                 Login                               |\n\
|                                                                     |\n\
|                                                                     |\n\
|                                 1.Login                             |\n\
|                                                                     |\n\
|                                 2.Register                          |\n\
|                                                                     |\n\
|                                 3.Quit                              |\n\
|                                                                     |\n\
|                                                                     |\n\
|                                                                     |\n\
-----------------------------------------------------------------------\n\
 ";

const char* choose_ = "\
|  «Î ‰»Î: ";
