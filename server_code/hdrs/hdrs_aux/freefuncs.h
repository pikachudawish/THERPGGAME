#ifndef FREEFUNCS_H
#define FREEFUNCS_H

void free_adv(adv* a);
void free_dbtask(dbtask* db_queue_head);
void free_sendtask(packagelist* pkg_queue_head);

#endif