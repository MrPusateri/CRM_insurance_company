# CRM FOR AN INSURANCE COMAPNY

InsuraPro Solutions is a software company that aims to improve the efficiency and quality of insurance customer service. InsuraPro wants to offer an interactive console application developed in C++ that allows the users to manage customers information and their interactions with the insurance company effectively and intuitively.

The project requirements are:
1. OOP in C++: implementing the OOP concepts in order to gurantee a robust and flexible structure.
2. Data structure: create a data structure to store information about customers and their interactions.
3. User Interface: Develop an interactive and intuitive command-line interface.
4. Features:
    * Adding a Customer: entering new customers into CRM.
    * Client display: display all clients present.
    * Edit a client: edit the details of an existing client.
    * Deleting a customer: removing customers from CRM.
    * Search for a customer: search for customers by first or last name.
    * Interaction management: add, view, and search interactions for each customer (interactions are defined as appointments by the sales force and contracts signed).
    * Saving and loading data: save customer and interaction data in a file (text or csv) and load it at startup.
    * User interface: the interface will be command-line based, with a main menu offering clear options for all necessary operations, ensuring a smooth and accessible user experience.

## Data structures

In order to create a rubust software we have to start to define the data structure we want to use. The requirements of the project give us a hint, since they describe like two different kind of information customers and their interactions with the insurance company.

Hence, we create two different files, one to store customer information such as name and surname, the second to store customer interactions. The two files have a relationship through a key named `customer_ID`. In particular, the `customer_ID` is an unique identifier for each customer in the customers file, whereas in the interactions file we can have **n** occurrences of the `customer_ID`, where **n** depends on the number of interactions between the insurance company and the customer.

### Customers

The customers file is like a database table where store the personal information about a customer. Depending on the state in which we collect data, we may have access to different customer information because privacy laws are different. The database layout we want to use is:
* **`CUSTOMER_ID`**, it is the unique identifier for each customer in the customers database.
* **`NAME`**, name of the customer.
* **`SURNAME`**, surname of the customer.
* **`BDAY`**, birthday of the customer. The date format is **DD/MM/YYYY**.
* **`TAX_CODE`**, generally speaking, a state has an identifier for each citizen, and with this information various socioeconomic information can be accessed. In this project, the data recorded in the file have no meaning and are for experimental purposes only.

### Interactions

The interactions file is like a database table where store the interactions between customers and insurance company. The database layout is:
* **`CUSTOMER_ID`**, it is the unique identifier for each customer in the customers database.
* **`INTERCTION_TYPE`**, it is a string that represent the type of interaction stored by InsuraPro. The user can choose among 3 different kind of interaction type:
    * `APPOINTMENT`, it is when the sales force contact a customer.
    * `QUOTE`, it is when the customers ask for a quotation of the risk and the sales force give a quote, but the customer do not sign for it.
    * `SIGN`, it is when the customer sign an insurance policy.
* **`FLAG_INTEREST`**, is a boolean variable that can assume `true` values depending on the interest of the client during the interaction. For _SIGN_ interactions is always true. Instead, for _APPOINTMENT_ and _QUOTE_ can assume `false` and `true` values.
* **`PRODUCT_TYPE`**, it can take different values depending on the product discussed with customers by the sales force. In this example we use only three values:
    * `CAR`, car insurance.
    * `HEALTH`, health insurance.
    * `HOME`, property insurance.
* **`INTERACTION_DATE`**, it represents the date of the interaction.
* **`POLICY_ID`**, is an identifier of a client's underwritten policy. That ID can be useful if we implement other database with relevant information about policies.
* **`QUOTES_ID`**, is an identifier of a client's quote. That ID can be useful if we implement other database with relevant information about quotes.

### Persistent `CUSTOMER_ID`

The variable `CUSTOMER_ID` is persistent. When I add a new customer to my CRM, the value of the new identifier should be the maximum number of all registered `CUSTOMER_ID` (both in the interactions table and the customers table) + 1. Instead, when a new data-base is used the persistent identifier should be refreshed and coherent with the new data.

Hence, the file **`next_customer_id.txt`** store the next value of the identifier following the rules described before.

## Features

In the next sections I present the features of the InsuraPro's CRM.

### Adding a customer

To add a new customer to the InsuraPro's CRM the user has to select the option add customer.

After through the terminal the sofware ask some foundamental information that are NAME and SURNAME.

### Client display: display all clients present.

### Edit a client: edit the details of an existing client.

### Deleting a customer: removing customers from CRM.

### Search for a customer

search for customers by first or last name.

### Interaction management

or each customer (interactions are defined as appointments by sales force and contracts signed).

### Saving and loading data

Customer and interaction data are stored in two separate CSV files, named `customers.csv` and `interactions.csv` respectively.

### User interface