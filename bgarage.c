#include <stdio.h>
#include <stdlib.h>

#define MAX_USERS 100
#define MAX_TRANSACTIONS_PER_USER 100

typedef struct {
    int user_id;
    int transaction_num;
    int requested_time;
    int duration;
} Transaction;

int main() {
    Transaction transactions[MAX_USERS * MAX_TRANSACTIONS_PER_USER];
    int total_transactions = 0;
    int num_users;
    
    printf("Enter the number of users: ");
    scanf("%d", &num_users);
    
    // Read input for all users
    for (int u = 1; u <= num_users; u++) {
        int user_id, start_time, num_trans;
        
        printf("Enter data for User %d\n", u);
        printf("Enter user ID: ");
        scanf("%d", &user_id);
        printf("Enter starting time: ");
        scanf("%d", &start_time);
        printf("Enter the number of transactions: ");
        scanf("%d", &num_trans);
        
        int durations[MAX_TRANSACTIONS_PER_USER];
        printf("Enter the durations of the transactions: ");
        for (int t = 0; t < num_trans; t++) {
            scanf("%d", &durations[t]);
        }
        
        // Create transaction records for this user
        int current_time = start_time;
        for (int t = 0; t < num_trans; t++) {
            transactions[total_transactions].user_id = user_id;
            transactions[total_transactions].transaction_num = t + 1;
            transactions[total_transactions].requested_time = current_time;
            transactions[total_transactions].duration = durations[t];
            
            current_time += durations[t];
            total_transactions++;
        }
    }
    
    // Sort transactions by requested time (bubble sort)
    for (int i = 0; i < total_transactions - 1; i++) {
        for (int j = 0; j < total_transactions - i - 1; j++) {
            if (transactions[j].requested_time > transactions[j + 1].requested_time) {
                Transaction temp = transactions[j];
                transactions[j] = transactions[j + 1];
                transactions[j + 1] = temp;
            }
        }
    }
    
    // Simulate processing
    int current_time = 0;
    int total_waiting_time = 0;
    
    printf("\n--- Simulation Results ---\n");
    for (int i = 0; i < total_transactions; i++) {
        Transaction *t = &transactions[i];
        
        // If CPU is idle, jump to requested time
        if (current_time < t->requested_time) {
            current_time = t->requested_time;
        }
        
        int waiting_time = current_time - t->requested_time;
        int start_time = current_time;
        int end_time = current_time + t->duration;
        
        printf("User %d Transaction %d: Start time: %d End time: %d Waiting time: %d - %d = %d seconds\n",
               t->user_id, t->transaction_num, start_time, end_time, 
               start_time, t->requested_time, waiting_time);
        
        total_waiting_time += waiting_time;
        current_time = end_time;
    }
    
    // Calculate and print average waiting time
    float average_waiting = (float)total_waiting_time / total_transactions;
    printf("\nAverage waiting time: %.2f seconds\n", average_waiting);
    
    return 0;
}




flowchart TD
    START([START]) --> INIT[Initialize data structures<br/>total_transactions = 0]
    
    INIT --> INPUT_N[Print: Enter number of users<br/>Read num_users]
    
    INPUT_N --> VALID_N{num_users valid?}
    VALID_N -->|No| ERROR[Display error & EXIT]
    VALID_N -->|Yes| USER_LOOP_START[user_counter = 1]
    
    USER_LOOP_START --> USER_CHECK{user_counter <= num_users?}
    
    USER_CHECK -->|Yes| READ_USER[Print: Enter data for User X<br/>Read user_id, start_time, num_trans]
    
    READ_USER --> READ_DURS[Read num_trans durations<br/>into durations array]
    
    READ_DURS --> CREATE_SUB[Call Sub-process: Create Transactions]
    
    CREATE_SUB --> USER_INC[user_counter++]
    USER_INC --> USER_CHECK
    
    USER_CHECK -->|No| SORT[Sort transactions by requested_time]
    
    SORT --> SIM_INIT[Initialize:<br/>current_time = 0<br/>total_waiting = 0<br/>completed = 0]
    
    SIM_INIT --> TRANS_LOOP[i = 0]
    
    TRANS_LOOP --> TRANS_CHECK{i < total_transactions?}
    
    TRANS_CHECK -->|Yes| GET_TRANS[t = transactions[i]]
    
    GET_TRANS --> IDLE_CHECK{current_time < t.requested_time?}
    
    IDLE_CHECK -->|Yes| UPDATE_TIME[current_time = t.requested_time]
    IDLE_CHECK -->|No| CALC_WAIT
    
    UPDATE_TIME --> CALC_WAIT[waiting = current_time - t.requested_time]
    
    CALC_WAIT --> CALC_START[start = current_time]
    CALC_START --> CALC_END[end = current_time + t.duration]
    
    CALC_END --> PRINT[Print: User X Transaction Y<br/>Start: start End: end<br/>Waiting: start - requested = waiting]
    
    PRINT --> UPDATE_ACC[total_waiting += waiting<br/>completed++]
    
    UPDATE_ACC --> UPDATE_CURR[current_time = end]
    
    UPDATE_CURR --> TRANS_INC[i++]
    TRANS_INC --> TRANS_CHECK
    
    TRANS_CHECK -->|No| CALC_AVG[average = total_waiting / completed]
    
    CALC_AVG --> PRINT_AVG[Print: Average waiting time: average seconds]
    
    PRINT_AVG --> END([END])
    
    ERROR --> END
    
    %% Sub-process styling
    style CREATE_SUB fill:#f9f,stroke:#333,stroke-width:2px


flowchart TD
    SUB_START([SUB: Create Transaction Records]) --> INIT_REQ[req_time = start_time<br/>t_counter = 1]
    
    INIT_REQ --> SUB_LOOP{t_counter <= num_trans?}
    
    SUB_LOOP -->|Yes| CREATE[Create new Transaction:<br/>user_id = user_id<br/>transaction_num = t_counter<br/>requested_time = req_time<br/>duration = durations[t_counter-1]]
    
    CREATE --> ADD[Add to transactions array<br/>total_transactions++]
    
    ADD --> UPDATE_REQ[req_time += durations[t_counter-1]]
    
    UPDATE_REQ --> SUB_INC[t_counter++]
    
    SUB_INC --> SUB_LOOP
    
    SUB_LOOP -->|No| SUB_RETURN([Return to Main])