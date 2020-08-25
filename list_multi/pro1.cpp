#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "pro1.h"
#include "jsmn.h"


char * aux_recv_data  = (char*)"{\"pld\":\"123pld321PLMID1a\",\"app_info\":{\"name\":\"dc\",\"svc\":\"11SVC11SVC\",\"eid\":\"11111111111111111111111111111111111111111111111111\",\"vid\":\"0VID1111\",\"aid\":\"011AID1111\"},\"app_info\":{\"name\":\"Connected_worker\",\"svc\":\"22SVC22SVC\",\"eid\":\"22222222222222222222222222222222222222222222222222\",\"vid\":\"0VID2222\",\"aid\":\"022AID2222\"},\"app_info\":{\"name\":\"People_Traker\",\"svc\":\"33SVC33SVC\",\"eid\":\"33333333333333333333333333333333333333333333333333\",\"vid\":\"0VID3333\",\"aid\":\"033AID3333\"}}";
/*************************************************************************************************************
 Golbal list act as Head Node
 ************************************************************************************************************/
jiot_client_nbiot_nidd_aux_data_t *head_node = NULL;


static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

int jiot_client_nbiot_nidd_parse_app_details(char *json_string,char *plmid,jiot_client_nbiot_nidd_app_details_t *appDetails){
    int tkn_iteration;
	int tkn_cnt;
    int length = 0;
	jsmn_parser p;
	jsmntok_t t[128];
	jsmn_init(&p);

    //storing plmid in each app set
    appDetails->plmid = (char *)calloc(length,sizeof(char));
    if(!appDetails->plmid){
        printf("Memory allocation failed for appDetails->plmid\n");
        return NO_MEMORY;
    }
    strncpy(appDetails->plmid,plmid,strlen(plmid));

	tkn_cnt = jsmn_parse(&p, json_string, strlen(json_string), t, sizeof(t)/sizeof(t[0]));
	if (tkn_cnt < 0) {
		printf("Failed to parse JSON: %d\n", tkn_cnt);
		return INVALID_PARAM;
	}
	if (tkn_cnt < 1 || t[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		return INVALID_PARAM;
    }

	for (tkn_iteration = 1; tkn_iteration < tkn_cnt; tkn_iteration++) {
        if (jsoneq(json_string, &t[tkn_iteration], "name") == 0) {
            length = t[tkn_iteration+1].end-t[tkn_iteration+1].start+1;
            appDetails->appName = (char *)calloc(length,sizeof(char));
            if(!appDetails->appName){
                printf("Memory allocation failed for appDetails->appName\n");
                return NO_MEMORY;
            }
            strncpy(appDetails->appName,json_string+t[tkn_iteration+1].start,length-1);
            // printf("appDetails->appName : %s\n",appDetails->appName);
			tkn_iteration++;
		}
		else if (jsoneq(json_string, &t[tkn_iteration], "svc") == 0) {
            length = t[tkn_iteration+1].end-t[tkn_iteration+1].start+1;
            appDetails->svc = (char *)calloc(length,sizeof(char));
            if(!appDetails->svc){
                printf("Memory allocation failed for appDetails->svc\n");
                return NO_MEMORY;
            }
            strncpy(appDetails->svc,json_string+t[tkn_iteration+1].start,length-1);
            // printf("appDetails->svc : %s\n",appDetails->svc);
			tkn_iteration++;
		}
        else if (jsoneq(json_string, &t[tkn_iteration], "eid") == 0) {
            length = t[tkn_iteration+1].end-t[tkn_iteration+1].start+1;
            appDetails->eid = (char *)calloc(length,sizeof(char));
            if(!appDetails->eid){
                printf("Memory allocation failed for appDetails->eid\n");
                return NO_MEMORY;
            }
            strncpy(appDetails->eid,json_string+t[tkn_iteration+1].start,length-1);
            // printf("appDetails->eid : %s\n",appDetails->eid);
			tkn_iteration++;
		}
        else if (jsoneq(json_string, &t[tkn_iteration], "vid") == 0) {
            length = t[tkn_iteration+1].end-t[tkn_iteration+1].start+1;
            appDetails->vid = (char *)calloc(length,sizeof(char));
            if(!appDetails->vid){
                printf("Memory allocation failed for appDetails->vid\n");
                return NO_MEMORY;
            }
            strncpy(appDetails->vid,json_string+t[tkn_iteration+1].start,length-1);
            // printf("appDetails->vid : %s\n",appDetails->vid);
			tkn_iteration++;
		}
        else if (jsoneq(json_string, &t[tkn_iteration], "aid") == 0) {
            length = t[tkn_iteration+1].end-t[tkn_iteration+1].start+1;
            appDetails->aid = (char *)calloc(length,sizeof(char));
            if(!appDetails->aid){
                printf("Memory allocation failed for appDetails->aid\n");
                return NO_MEMORY;
            }
            strncpy(appDetails->aid,json_string+t[tkn_iteration+1].start,length-1);
            // printf("appDetails->aid : %s\n",appDetails->aid);
			tkn_iteration++;
		} 
	}
    return SUCCESS;
}

int jiot_client_nbiot_nidd_parse_aux_data(char *json_string,jiot_client_nbiot_nidd_aux_data_t *aux_data){
    int tkn_iteration;
	int tkn_cnt;
    int length = 0;
	jsmn_parser p;
	jsmntok_t t[128];
	jsmn_init(&p);
    char *app_info = NULL;
    int count = 0;
    char *plmid;
    jiot_client_nbiot_nidd_app_details_t *appDeatils = NULL;

	tkn_cnt = jsmn_parse(&p, json_string, strlen(json_string), t, sizeof(t)/sizeof(t[0]));
	if (tkn_cnt < 0) {
		printf("Failed to parse JSON: %d\n", tkn_cnt);
		return INVALID_PARAM;
	}
	if (tkn_cnt < 1 || t[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		return INVALID_PARAM;
    }

	for (tkn_iteration = 1; tkn_iteration < tkn_cnt; tkn_iteration++) {
        if (jsoneq(json_string, &t[tkn_iteration], "pld") == 0) {
            length = t[tkn_iteration+1].end-t[tkn_iteration+1].start+1;
            plmid = (char *)calloc(length,sizeof(char));
            if(!plmid){
                printf("Memory allocation failed for plmid\n");
                return NO_MEMORY;
            }
            strncpy(plmid,json_string+t[tkn_iteration+1].start,length-1);
            // printf("aux_data->pld : %s\n",aux_data->pld);
			tkn_iteration++;
		}
		else if (jsoneq(json_string, &t[tkn_iteration], "app_info") == 0) {
            length = t[tkn_iteration+1].end-t[tkn_iteration+1].start+1;
            app_info = (char *)calloc(length,sizeof(char));
            if(!app_info){
                printf("Memory allocation failed for apps_info\n");
                return NO_MEMORY;
            }
            strncpy(app_info,json_string+t[tkn_iteration+1].start,length-1);
            appDeatils = (jiot_client_nbiot_nidd_app_details_t *)malloc(sizeof(jiot_client_nbiot_nidd_app_details_t));
            if(!appDeatils){
                printf("Memory allocation for appDetails : Failed\n");
                return NO_MEMORY;
            }
            memset(appDeatils,0,sizeof(jiot_client_nbiot_nidd_app_details_t));
            add_Node_to_list(appDeatils);
            jiot_client_nbiot_nidd_parse_app_details(app_info,plmid,appDeatils);
            // printf("Count : %d\tappName : %s\n",count,app_info);
			tkn_iteration++;
            count++;
		} 
	}
    return SUCCESS;
}

/*************************************************************************************************************
 @display_listc : print all the value of a list
 ************************************************************************************************************/
void display_list(){
    jiot_client_nbiot_nidd_aux_data_t *temp_node = head_node; 
    while(temp_node!=NULL){
        printf("Pld : %s\n",temp_node->appDetails->plmid);
        printf("app : %s\n",temp_node->appDetails->appName);
        printf("svc : %s\n",temp_node->appDetails->svc);
        printf("eid : %s\n",temp_node->appDetails->eid);
        printf("vid : %s\n",temp_node->appDetails->vid);
        printf("aid : %s\n",temp_node->appDetails->aid);
        printf("\n\n");
        // printf("temp : %p\n",temp_node);
        temp_node = temp_node->next;
    }
    printf("\n\n");
}

/*************************************************************************************************************
 @add_Node_to_list : Adding Node in a list.
 @user_data : value of int which is adding in list
 ************************************************************************************************************/
int add_Node_to_list(jiot_client_nbiot_nidd_app_details_t *app_Details){
    jiot_client_nbiot_nidd_aux_data_t *curr_node = NULL;
    jiot_client_nbiot_nidd_aux_data_t *temp_node = NULL;

    curr_node = (jiot_client_nbiot_nidd_aux_data_t *)malloc(sizeof(jiot_client_nbiot_nidd_aux_data_t));
    if(!curr_node){
        printf("Memory allocation for current Node : Failed\n");
        return FAILURE;
    }
    memset(curr_node,0,sizeof(jiot_client_nbiot_nidd_aux_data_t));
    curr_node->appDetails = app_Details;
    if(head_node==NULL){
        head_node = curr_node;
    }
    else{
        temp_node=head_node;
        while(temp_node->next!=NULL){
            temp_node = temp_node->next;
        }
        temp_node->next = curr_node;
    }
    return SUCCESS;
    
}

/*************************************************************************************************************
 @find_Node_in_list : Searching Node in list.
 @user_data : value of int which is Searching in list
 ************************************************************************************************************/
jiot_client_nbiot_nidd_aux_data_t* find_Node_in_list(char *appName){
    // printf("User appname : %s\n",appName);
    int i=1;
    jiot_client_nbiot_nidd_aux_data_t *temp_node = head_node; 
    while(temp_node!=NULL){
        if(!strcmp(temp_node->appDetails->appName,appName)){
            // printf("appname : %s\n",temp_node->appDetails->appName);
            return (temp_node);
        }
        temp_node=temp_node->next;
        i++;
    }
    printf("No Match found\n");
    return NULL;
}


int main(){
    char app_name[30];
    

    jiot_client_nbiot_nidd_aux_data_t *auxData = NULL;
    jiot_client_nbiot_nidd_aux_data_t *user_app = NULL;
    auxData = (jiot_client_nbiot_nidd_aux_data_t *)malloc(sizeof(jiot_client_nbiot_nidd_aux_data_t));
    if(!auxData){
        printf("Memory allocation for auxData : Failed\n");
    }
    memset(auxData,0,sizeof(jiot_client_nbiot_nidd_aux_data_t));
    jiot_client_nbiot_nidd_parse_aux_data(aux_recv_data,auxData);
    display_list();
    printf("enter appName : ");
    scanf("%s",&app_name);
    user_app = find_Node_in_list(app_name);
    if(user_app!=NULL){
        printf("Pld : %s\n",user_app->appDetails->plmid);
        printf("app : %s\n",user_app->appDetails->appName);
        printf("svc : %s\n",user_app->appDetails->svc);
        printf("eid : %s\n",user_app->appDetails->eid);
        printf("vid : %s\n",user_app->appDetails->vid);
        printf("aid : %s\n",user_app->appDetails->aid);
    }
    else{
        printf("Invaild appName \n");
    }

    return 0;
}