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

In this sections I present the features of the InsuraPro's CRM and the user interface.

### User interface

The user interface is the standard terminal output where the user runs the application. Specifically, the following line must be executed to create the executable `CRM_INSURA_PRO`:
```console
g++ -std=c++17 -o ./CRM_INSURA_PRO ./main.cpp ./CustomerManager.cpp ./Customer.cpp ./my_functions.cpp ./Interaction.cpp ./InteractionManager.cpp
```

**Note that:** InsuraPro's CRM uses the C++17 standard in that it uses features such as `std::optional<...>` and `std::nullopt` to keep the code clearer and more maintainable.

There are two main methods the user has to interact with the application:
* The application print in the terminal a list of possible action to execute, where the bullet points are integer number inside square brackets. The user has to insert the integer value related to action to execute.

    Example:

    ```console
    Enter the number in bracketsthat corresponds to the product related to the interaction:
    [1] CAR.
    [2] HEALTH.
    [3] HOME.
    You chose: 2
    ```

    In this example the interaction is related to a `HEALTH` product.
* The application prints a question in the terminal and at the end there is a square bracket like `[y/n]` and the user has to enter a character `y` (yes) or 'n' (no) to express a decision.

    Example:

    ```console
    It is correct?[y/n] y
    ```

A user in order to select a functionality of InsuraPro's CRM has to make a decision of the following menu:
```console
The possible actions are:
 [1] Upload a CSV  file that  contains a  CRM  with the  same structure
     presented in the documentation.
 [2] Upload a CSV file that contains interactions with  customers  with
     the same rules in the documentation.
 [3] Add a customer.
 [4] Display all the customers.
 [5] Edit a customer.
 [6] Delete a customer.
 [7] Search a customer.
 [8] Add a new interaction.
 [9] Display all the interactions.
[10] Search interactions of a customer.
[11] Save CRM data.
[12] Save interaction data.
[13] Save all and exit.
[14] Exit without saving.
You chose:
```

Next sections present the different oprions.

### Upload a CRM csv file

The user has to insert the file path that points to a CSV file that has the same structure of the Customer table presented i this documentation.

```console
Insert the customers CSV file name: customers.csv
```

In this case the csv file is in the same folder of the executable.

### Upload an interactions csv file

The user has to insert the file path that points to a CSV file that has the same structure of the Interaction table presented i this documentation.

```console
Insert the interactions CSV file name: interactions.csv
```

In this case the csv file is in the same folder of the executable.

### Add a customer

To add a new customer to the InsuraPro's CRM the user has to select the option `[3] Add a customer.`. After the program starts to ask all the required information necessary for a customer:
* name, the customer name.
* surname, the customer surname.
* birth day, the customer birth day in the format `DD/MM/YYYY`.
* tax code, the customer tax code that has a different structure depending on the cuntry. It accept only letters and numbers.

When the user ends to insert all the necessary information, the InsuraPro's CRM program shows the customer to add and ask to the user if it is correct or not `It is correct?[y/n] ` if the user say `y`, the program ask a new action to the user. Otherwise, ask if the user want to continue to add a new customer or not.

### Display all customers

The action `[4] Display all the customers.` shows on the terminal a table with all the customers in the customer manager.

### Edit a customer

The action `[5] Edit a customer.` allow the user to modify information related to a customer in the CRM. The user has to select the customer through the name or surname and select the specific customer using the `CUSTOMER_ID` associated. After, the user decided which information change and which not.

### Delete a customer

The action `[6] Delete a customer.` drives the user to delete a customer from the InsuraPro's CRM.

### Search for a customer

The action `[7] Search a customer.` drives the user to search a customer from the InsuraPro's CRM. It is possible to search a customer by full name or full surname.

### Add an interaction

The action `[8] Add a new interaction.` drives the user to insert a new interaction linked to a customer in the CRM. Depending on the interaction type the InsuraPro's CRM asks different information to insert.

### Display interactions

The action `[9] Display all the interactions.` shows on the terminal a table with all the interactions in the CRM.

### Search interactions of a customer

The action `[10] Search interactions of a customer.` allows to search all the interactions linked to a specific customer that has to be search by the user using the full name or surname.

### Saving data and exit

The last possible actions are:
* `[11] Save CRM data.`, the user has to specify a valid path to save the customer table.
* `[12] Save interaction data.`, the user has to specify a valid path to save the interaction table.
* `[13] Save all and exit.`, the user has to specify a valid path to save the customer and the interactions tables and after the program ends.
* `[14] Exit without saving.`, the program ends without saving anything.