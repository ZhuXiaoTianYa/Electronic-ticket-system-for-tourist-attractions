#include "Visual_interface.h"


int pos_ = static_cast<int>(Scene::Start_Sc);
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
