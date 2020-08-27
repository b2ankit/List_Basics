#ifndef PRO1_H
#define PRO1_H

#ifdef __cplusplus
extern "C"{
#endif
/*************************************************************************************************************
 Define MACROS
 ************************************************************************************************************/
    #define SUCCESS 1
    #define FAILURE -1
    #define NO_MEMORY -2
    #define INVALID_PARAM -3
    #define INVALID_APPNAME -4
    #define VALID_APPNAME 2
/*************************************************************************************************************
 Define struct
 ************************************************************************************************************/
    typedef struct jiot_client_nbiot_nidd_app_details_t
    {
        char *appName;
        char *svc;
        char *eid;
        char *vid;
        char *aid;
    }jiot_client_nbiot_nidd_app_details_t;
    
    typedef struct aux_data
    {
        char *plmid;
        jiot_client_nbiot_nidd_app_details_t *appDetails;
        struct aux_data *next;
    }jiot_client_nbiot_nidd_aux_data_t;
    
/*************************************************************************************************************
 
 ************************************************************************************************************/
int jiot_client_nbiot_nidd_parse_app_details(char *json_string,char *plmid);


/*************************************************************************************************************
 
 ************************************************************************************************************/
int jiot_client_nbiot_nidd_parse_aux_data(char *json_string);


/*************************************************************************************************************
 
 ************************************************************************************************************/
void display_list();


/*************************************************************************************************************
 
 ************************************************************************************************************/

/*************************************************************************************************************
 @add_Node_to_list : Adding Node in a list.
 @user_data : value of int which is adding in list
 ************************************************************************************************************/
int add_Node_to_list(char *plmid,jiot_client_nbiot_nidd_app_details_t *app_Details);

/*************************************************************************************************************
 @find_Node_in_list : Searching Node in list.
 @user_data : value of int which is Searching in list
 ************************************************************************************************************/
jiot_client_nbiot_nidd_aux_data_t* find_Node_in_list(char *appName);

void jiot_client_nbiot_nidd_auxData_receive();

#ifdef __cplusplus
}
#endif

#endif //PRO1_H