#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <poll.h>

#include "../../hdrs/hdrs_structs/structs_server.h"
#include "../../hdrs/hdrs_aux/globalvariable.h"
#include "../../enums.h"

int pkg_vrf_ui(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_vrf_ui())\n");
        return 0;
    }

    new_task->type = DBTASK_VRF_UI;
    new_task->client_fd = fd;

    user_info* ui = (user_info*)malloc(sizeof(user_info));
    if(!ui) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (ui pkg_get_adv())\n");
        free(new_task);
        return 0;
    }

    strcpy(ui->username, pkg->data.ui.username);
    strcpy(ui->pass, pkg->data.ui.pass);
    
    new_task->data = ui;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_get_adv(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_get_adv())\n");
        return 0;
    }

    new_task->type = DBTASK_GET_ADV;
    new_task->client_fd = fd;
    
    user_info* ui = (user_info*)malloc(sizeof(user_info));
    if(!ui) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (ui pkg_get_adv())\n");
        free(new_task);
        return 0;
    }

    strcpy(ui->username, pkg->data.ui.username);

    new_task->data = ui;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_ins_ui(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_ins_ui())\n");
        return 0;
    }

    new_task->type = DBTASK_INS_UI;
    new_task->client_fd = fd;

    user_info* ui = (user_info*)malloc(sizeof(user_info));
    if(!ui) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (ui pkg_ins_ui())\n");
        free(new_task);
        return 0;
    }


    *ui = pkg->data.ui;
    strcpy(ui->username, pkg->data.ui.username);
    strcpy(ui->pass, pkg->data.ui.pass);
    
    new_task->data = ui;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_add_adv_to_user(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_add_adv_to_use())\n");
        return 0;
    }

    new_task->type = DBTASK_ADD_ADV_TO_USER;
    new_task->client_fd = fd;

    int* ids = (int*)malloc(2 * sizeof(int));
    if(!ids) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (ids pkg_add_adv_to_user())\n");
        free(new_task);
        return 0;
    }

    *ids = pkg->data.ids;
    new_task->data = ids;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_ins(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_ins())\n");
        return 0;
    }

    new_task->type = DBTASK_INS;
    new_task->client_fd = fd;

    adv* aux = (adv*)malloc(sizeof(adv));
    if(!aux) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (aux pkg_ins())\n");
        free(new_task);
        return 0;
    }
    *aux = pkg->data.adventurer;
    new_task->data = aux;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_upd_adv(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_upd_adv())\n");
        return 0;
    }

    new_task->type = DBTASK_UPD_ADV;
    new_task->client_fd = fd;

    adv* aux = (adv*)malloc(sizeof(adv));
    if(!aux) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (aux pkg_upd_adv())\n");
        free(new_task);
        return 0;
    }
    *aux = pkg->data.adventurer;
    new_task->data = aux;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_upd_s(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_ups_s())\n");
        return 0;
    }

    new_task->type = DBTASK_UPD_S;
    new_task->client_fd = fd;

    stats* aux = (stats*)malloc(sizeof(stats));
    if(!aux) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (aux pkg_upd_s())\n");
        free(new_task);
        return 0;
    }
    *aux = pkg->data.s;
    new_task->data = aux;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_upd_m(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_upd_m())\n");
        return 0;
    }

    new_task->type = DBTASK_UPD_M;
    new_task->client_fd = fd;

    moves* aux = (moves*)malloc(sizeof(moves));
    if(!aux) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (aux pkg_upd_m())\n");
        free(new_task);
        return 0;
    }
    *aux = pkg->data.m;
    new_task->data = aux;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_upd_e(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_upd_e())\n");
        return 0;
    }

    new_task->type = DBTASK_UPD_E;
    new_task->client_fd = fd;

    equipment* aux = (equipment*)malloc(sizeof(equipment));
    if(!aux) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (aux pkg_upd_e())\n");
        free(new_task);
        return 0;
    }
    *aux = pkg->data.e;
    new_task->data = aux;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_upd_h(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_upd_h())\n");
        return 0;
    }

    new_task->type = DBTASK_UPD_H;
    new_task->client_fd = fd;

    helmet_stats* aux = (helmet_stats*)malloc(sizeof(helmet_stats));
    if(!aux) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (aux pkg_upd_h())\n");
        free(new_task);
        return 0;
    }
    *aux = pkg->data.h;
    new_task->data = aux;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_upd_c(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_upd_c())\n");
        return 0;
    }

    new_task->type = DBTASK_UPD_C;
    new_task->client_fd = fd;

    chestplate_stats* aux = (chestplate_stats*)malloc(sizeof(chestplate_stats));
    if(!aux) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (aux pkg_upd_c())\n");
        free(new_task);
        return 0;
    }
    *aux = pkg->data.c;
    new_task->data = aux;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_upd_a(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_upd_a())\n");
        return 0;
    }

    new_task->type = DBTASK_UPD_A;
    new_task->client_fd = fd;

    armlet_stats* aux = (armlet_stats*)malloc(sizeof(armlet_stats));
    if(!aux) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (aux pkg_upd_a())\n");
        free(new_task);
        return 0;
    }
    *aux = pkg->data.a;
    new_task->data = aux;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_upd_b(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_upd_b())\n");
        return 0;
    }

    new_task->type = DBTASK_UPD_B;
    new_task->client_fd = fd;

    boots_stats* aux = (boots_stats*)malloc(sizeof(boots_stats));
    if(!aux) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (aux pkg_upd_b())\n");
        free(new_task);
        return 0;
    }
    *aux = pkg->data.b;
    new_task->data = aux;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_upd_w(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_upd_w())\n");
        return 0;
    }

    new_task->type = DBTASK_UPD_W;
    new_task->client_fd = fd;

    weapon_stats* aux = (weapon_stats*)malloc(sizeof(weapon_stats));
    if(!aux) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (aux pkg_upd_w())\n");
        free(new_task);
        return 0;
    }
    *aux = pkg->data.w;
    new_task->data = aux;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}

int pkg_rmv(int fd, package* pkg) {
    dbtask* new_task = (dbtask*)malloc(sizeof(dbtask));
    if(!new_task) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (new_task pkg_rmv())\n");
        return 0;
    }

    new_task->type = DBTASK_RMV;
    new_task->client_fd = fd;

    adv* aux = (adv*)malloc(sizeof(adv));
    if(!aux) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (aux pkg_upd_rmv())\n");
        free(new_task);
        return 0;
    }
    *aux = pkg->data.adventurer;
    new_task->data = aux;
    new_task->next = NULL;

    pthread_mutex_lock(&db_mutex);

    if(!db_queue_tail) { 
        db_queue_head = new_task;
        db_queue_tail = new_task;
    } else {
        db_queue_tail->next = new_task;
        db_queue_tail = new_task;
    }

    pthread_cond_signal(&db_cond);
    pthread_mutex_unlock(&db_mutex);

    return 1;
}
