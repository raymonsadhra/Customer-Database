#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//hash function by Mr. Bernstein
unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while (*str != '\0') {
    c = *str;
    hash = ((hash << 5) + hash) + (unsigned char)c; /* hash * 33 + c */
    str++;
  }
  return hash;
}

//struct for customer
typedef struct ll_customer{
        char *email;
        char *name;
        int *size;
        char *fav_food;
        struct ll_customer *next;
} ll_customer;

//struct for hash table
typedef struct customer_hashtable {
        ll_customer **buckets;
        size_t num_buckets;
} customer_hashtable;

//making hash table
customer_hashtable *make(size_t num_buckets){
	customer_hashtable *table = calloc(1, sizeof(customer_hashtable));
	table->num_buckets = num_buckets;
        table->buckets = calloc(num_buckets, sizeof(ll_customer *));
        return table;
}


//add function
ll_customer *add(char *email, char *name, int *size, char *fav_food, ll_customer *list){
        ll_customer *new_node = calloc(1, sizeof(ll_customer));
        new_node->email = strdup(email);
        new_node->name = strdup(name);
        new_node->size = malloc(sizeof(int));
	*(new_node->size) = *size;
        new_node->fav_food = strdup(fav_food);
        new_node->next = list;

        return new_node;
}

//add with hash function
void add_to_hashtable(customer_hashtable *table, char *email, char *name, int size, char *fav_food){
        unsigned long hashval = hash(email);
        unsigned long index = hashval % table->num_buckets;

        ll_customer *bucket  = table->buckets[index];
        table->buckets[index] = add(email, name, &size, fav_food, bucket);
}


//add customers on file to hashtable
void current_customers(customer_hashtable *table, char *file){
	FILE *f  = fopen(file,"r");
	char line[256];
	while(fgets(line,sizeof(line),f)){
		char *email = strtok(line, "\t");
		char *name = strtok(NULL, "\t");
		int size = atoi(strtok(NULL, "\t"));
		char *fav_food = strtok(NULL, "\n");

		add_to_hashtable(table,email,name,size,fav_food);
	}
	fclose(f);

}

//look up function
ll_customer *lookup(char *email, ll_customer *list){
        if(!list){
                printf("Sadly the customer's email was unable to be found!");
		return NULL;
        }
        else if(!strcmp(list->email, email)){
                //return list;
		printf("Email: %s, Name: %s, Shoe Size: %d, Favorite Food: %s\n", 
			list->email, list->name, *(list->size), list->fav_food);
		return list;
        }
        else{
                return lookup(email, list->next);
        }
}

//look up with hash function
ll_customer *lookup_hashtable(char *email, customer_hashtable *table){
        unsigned long hashval = hash(email);
        unsigned long index = hashval % table->num_buckets;

        ll_customer *bucket = table->buckets[index];
        return lookup(email,bucket);

}

//delete function
ll_customer *delete(char *email, ll_customer *list){
	if(!list){
		printf("Sadly this email was unable to be found!");
		return NULL;
	}
	else if(!strcmp(list->email,email)){
		free(list->email);
        	free(list->name);
		free(list->size);
		free(list->fav_food);
        	ll_customer *next = list->next;

		free(list);
		return next;
	}
	else{
		list->next = delete(email, list->next);
		return list;	
	}
}
//delete with hash function
void delete_hashtable(char *email, customer_hashtable *table){
	unsigned long hashval = hash(email);
	unsigned long index = hashval % table->num_buckets;
	ll_customer *bucket = table->buckets[index];
	table->buckets[index] = delete(email,bucket);

}
//list function
void list(ll_customer *list){
	while(list){
		printf("Email: %s, Name: %s, Shoe Size: %d, Favorite Food: %s\n", 
				list->email, list->name, *(list->size), list->fav_food);
		list = list->next;
	}
}
//list with buckets
void list_hashtable(customer_hashtable *table){
	for(size_t i = 0; i<table->num_buckets; i++){
		if(table->buckets[i]){
			list(table->buckets[i]);
		}
	}
}

//save function
void save(customer_hashtable *table, char *file){
	FILE *f = fopen(file, "w");

	for(size_t i = 0; i<table->num_buckets; i++){
		ll_customer *bucket = table->buckets[i];
		while(bucket){
			fprintf(f, "%s\t%s\t%d\t%s\n", bucket->email, bucket->name, *(bucket->size), bucket->fav_food);
			bucket = bucket->next;
		}
	}
	fclose(f);

}

//quit function
void quit(customer_hashtable *table){
	for(size_t i = 0; i<table->num_buckets; i++){
		ll_customer *bucket = table->buckets[i];
		while(bucket){
			ll_customer *next = bucket->next;
			free(bucket->email);
			free(bucket->name);
			free(bucket->size);
			free(bucket->fav_food);
			free(bucket);
			bucket = next;
		
		}
	}
	free(table->buckets);
	free(table);
	exit(0);

}

//MAIN LOOP
int main(){
	size_t num_buckets = 100;
	customer_hashtable *table = make(num_buckets);
	current_customers(table, "customers.tsv");
	
	char prompt[10];

	int size;
	char email[256];
	char name[256];
	char fav_food[256];

	while(true){
		printf("Add, lookup, delete, list, save, or quit?");
		scanf("%s", prompt);

		if(!strcmp(prompt,"add")){

			printf("Enter email: ");
            		scanf("%s", email);
            		printf("Enter name: ");
            		scanf("%s", name);
            		printf("Enter shoe size: ");
            		scanf("%d", &size);
            		printf("Enter favorite food: ");
            		scanf("%s", fav_food);
		
			add_to_hashtable(table, email, name, size, fav_food);
		
		}
		else if(!strcmp(prompt,"lookup")){
			printf("Enter email: ");
			scanf("%s", email);

			lookup_hashtable(email, table);
			
		
		}
		else if(!strcmp(prompt,"delete")){
		
			printf("Enter email: ");
            		scanf("%s", email);
			delete_hashtable(email, table);
		}
		else if(!strcmp(prompt,"list")){
			list_hashtable(table);
		}
		else if(!strcmp(prompt,"save")){
			save(table, "customer.tsv");
		}
		else if(!strcmp(prompt,"quit")){
			quit(table);
		}
	}
		


}
