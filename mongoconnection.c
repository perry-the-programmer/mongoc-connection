#include<mongoc/mongoc.h>
#include<stdio.h>

int main(){
    const char *uri_string = "mongodb://localhost:27017";
    mongoc_uri_t *uri;
    mongoc_client_t *client;
    mongoc_database_t *database;
    mongoc_collection_t *collection;
    bson_t *insert;
    bson_error_t error;
    char *str;
    bool retval;

    mongoc_init();
    uri = mongoc_uri_new_with_error(uri_string, &error);
    if(!uri){
        printf("failed to parse uri %s, error messgage %s\n",uri_string,error.message);
        return 1;
    } 
    client = mongoc_client_new_from_uri(uri);
    mongoc_client_set_appname(client, "connect-example");
    database = mongoc_client_get_database(client,"classroom_db");
    collection = mongoc_client_get_collection(client,"classroom_db","stus");
    insert = BCON_NEW("hello",BCON_UTF8("world"));
    if(!mongoc_collection_insert_one(collection, insert, NULL, NULL, &error)){
        printf("could not insert error->%s\n",error.message);
    }else{
        printf("success\n");
    }

    bson_destroy(insert);

    mongoc_collection_destroy(collection);
    mongoc_database_destroy(database);
    mongoc_uri_destroy(uri);
    mongoc_client_destroy(client);
    mongoc_cleanup(); 
    return 0;
}

