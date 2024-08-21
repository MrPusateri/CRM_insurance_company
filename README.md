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

### Interactions

The interactions file is like a database table where store the interactions between customers and insurance company. The database layout is:
* `CUSTOMER_ID`, it is the unique identifier for each customer in the customers database.
* `INTERCTION_TYPE`, it is a string that represent the type of interaction stored by InsuraPro. The user can choose among 3 different kind of interaction type:
    * APPOINTMENT, it is when the sales force contact a customer.
    * QUOTE, it is when the customers ask for a quotation of the risk and the sales force give a quote, but the customer do not sign for it.
    * SIGN, it is when the customer sign an insurance policy.
* `PREMIUM`, it represent the amount of money (the currency depends on the state of the insurance company, I'm in Italy and so I will use euros). However, it is a flaoting point number. It will be valued only for QUOTE and SIGN