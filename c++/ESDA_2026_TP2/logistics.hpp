#ifndef LOGISTICS_HPP
#define LOGISTICS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <stack>
using namespace std;

/* CLASSES */

class Product; /** @brief Class to represent a product. */
class Client; /** @brief Class to represent a client. */
class Warehouse; /** @brief Class to represent a warehouse. */
class Order; /** @brief Class to represent a Order. */
class ProductManagement; /** @brief Class to represent all products. */
class ClientManagement; /** @brief Class to represent all clients. */
class WarehouseManagement; /** @brief Class to represent all warehouses. */
class Shipment; /** @brief Class to represent a shipment. */
class ShipmentManagement; /** @brief Class to represent all shipments. */

/* STRUCTS */
struct ProdQuan {
    Product *product; /** @brief pointer to product. */
    int quantity; /** @brief  quantity of the product*/
    /* --- Constructor --- */
    ProdQuan(Product *prod, int quant): product(prod), quantity(quant) {} 
};

class Product {
private:
    /* ATTRIBUTES */
    int productId; /** @brief product id */
    string name; /** @brief name */
    string category; /** @brief name */
    double weight; /** @brief weight */
    double price; /** @brief price */
    vector<int> componentIds; /** @brief Vector with all products components */
   
public:
    /* METHODS */

    /* --- Constructor --- */
    /** 
    *  @brief Product (parameterized) - Create an object of the class Product.
    *  @param id Product Id.
    *  @param n Name of the product.
    *  @param c Category of the product.
    *  @param w Weight of the product.
    *  @param p price of the product.
    *  @note  Initialize each attribute with the corresponding argument.
     */
    Product(int id, string n, string c, double w, double p); 

    /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the product's productId.
    *  @return 'productId' attribute.
    */
    int getId() const;

    /** 
    *  @brief  Get the product's name.
    *  @return 'name' attribute.
    */
    string getName() const;

    /** 
    *  @brief  Get the product's weight.
    *  @return 'weight' attribute.
    */
    double getWeight() const;

    /** 
    *  @brief  Get the product's price.
    *  @return 'price' attribute.
    */
    double getPrice() const;

    /** 
    *  @brief  Get the all products that are part of this product.
    *  @return 'componentIds' attribute.
    */
    vector<int> getComponents() const;
 
    /* --- Other Methods --- */

    /** 
    *  @brief  Add a new product to a composite product.
    *  @param  productId product Id.
    *  @param  ProdManager Object with all the products in the platform.
    *  @return 0 if the new products is added successfully | 1 if the new product already exists |
    *  @return -1 if the parameteres are invalid or compoent not exist
    */
    int addComponent(int productId, ProductManagement& ProdManagement);

    /** 
    *  @brief  Display the information of a Product.
    *  @return void
    */
    void displayProductInfo(ostream& o) const;

    /** 
    *  @brief Check if the product weight is equal to the total weight of all components products.
    *  @param  ProdManager Object with all the products in the platform.
    *  @return If there are no components, it returns 1.
    *  @return For components products, return 1 if equal and 0 if different.
    */
    int ChecktotalWeight(ProductManagement& ProdManagement) const;
};

class Client {
private:
    /* ATTRIBUTES */
    int clientId; /** @brief client id */
    string name; /** @brief name */
    string city; /** @brief city*/
    vector<int> vectorOrdersId; /** @brief Vector with orders id */
public:
    /* METHODS */

    /* --- Constructor --- */
    /** 
    *  @brief Client (parameterized) - Create an object of the class client.
    *  @param id Product Id.
    *  @param n Name of the client.
    *  @param c City of the client.
   
    *  @note  Initialize each attribute with the corresponding argument.
     */
    Client(int id, const string& n, const string& c) ;

     /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the client's clientId.
    *  @return 'clientId' attribute.
    */
    int getId() const;

    /** 
    *  @brief  Get the client's name.
    *  @return 'name' attribute.
    */
    string getName() const;

    /** 
    *  @brief  Get the client's city.
    *  @return 'city' attribute.
    */
    string getCity() const;

    /** 
    *  @brief  Get the all orders which belong to the client.
    *  @return 'listOrdersId' attribute.
    */
    vector<int> getVectorOrdersId() const;
        

  /** 
    *  @brief  Add a new order to a client.
    *  @param  ordId pointer to order.
    *  @return 0 if the new orderId is added successfully | 1 if the new orderId already exists |
    *  @return -1 if the parameteres are invalid or compoent not exist
    */
    int addOrder(int ordId);
};

class Warehouse {
private:
    /* ATTRIBUTES */
    int warehouseId; /** @brief warehouse id */
    string city;  /** @brief city */
    vector<pair<Product*,int>> vectorPQ; 
public:
    /* METHODS */

    /* --- Constructor --- */
    /** 
    *  @brief Warehouse (parameterized) - Create an object of the class warehouse.
    *  @param id Warehouse Id.
    *  @param c city.
    *  @param vp vector with all products.
    *  @param qp vector with all quantity.
    *  @note  Initialize each attribute with the corresponding argument.
     */
    Warehouse(int id, const string& c);
    Warehouse(int id, const string& c, vector<pair<Product*,int>> vpq);

    /* --- Get Methods --- */

    /** 
    *  @brief  Get the warehouse's warehouseId.
    *  @return 'warehouseId' attribute.
    */
    int getId() const;

    /** 
    *  @brief  Get the warehouse's city.
    *  @return 'city' attribute.
    */
    string getCity() const;


     /** 
    *  @brief  Get vector of pair of produxts and quantities.
    *  @return 'getVectorPQ' attribute.
    */
    vector<pair<Product*,int>> getVectorPQ() const;
    vector<pair<Product*,int>>& getVectorPQUpdate() ;

      /** 
    *  @brief  insert a product and its quantity into a warehouse.
    *  @param proI Id of the product.
    *  @param quant Quantity of the product.
    *  @return -1 if the parameteres are invalid or product not exist | 0 if the new product is added successfully | 1 if the new product already exists and the quantity is updated
    */
   int addProduct(int prodI, int quant, ProductManagement& PrManager);
};

class Order {
private:
    /* ATTRIBUTES */
    int orderId; /** @brief order id */
    Client* client; /** @brief pointer to client */
    Warehouse* warehouse; /** @brief pointer to warehouse */
    string date; /** @brief date of the order */
    vector<ProdQuan*> productQuant; /** @brief Vector with all produtcs and quantity  */
public:
    /* METHODS */

    /* --- Constructor --- */
    /** 
    *  @brief Order (parameterized) - Create an object of the class Order.
    *  @param id Order Id.
    *  @param cl  pointer to client.
    *  @param war pointer to warehouse.
    *  @param dat Date.
    *  @note  Initialize each attribute with the corresponding argument.
     */
    Order(int id,Client *cl,Warehouse *war,string dat);

       /* --- Get Methods --- */

    /** 
    *  @brief  Get the order's orderId.
    *  @return 'orderId' attribute.
    */
    int getId() const;

    /** 
    *  @brief  Get the order's client.
    *  @return 'client' attribute.
    */
    Client* getClient() const;

       /** 
    *  @brief  Get the order's warehouse.
    *  @return 'warehouse' attribute.
    */
    Warehouse* getWarehouse() const;

    /** 
    *  @brief  Get the vector wiht all products and quantity off the order.
    *  @return 'productQuant' attribute.
    */
    vector<ProdQuan*> getVectorProducts() const;
    
      /** 
    *  @brief  Add a new product to a order.
    *  @param  productId pointer to product.
    *  @param  quant Quantity of the product.
    *  @return 0 if the new product is added successfully | 1 if the new product already exists |
    *  @return -1 if the parameteres are invalid or compoent not exist
    */
    int addProduct(Product* prod, int quant);
};

class ClientManagement {
private:
    /* ATTRIBUTES */
    vector<Client*> vectorClients; /** @brief vector with all clients. */

public:
    /* METHODS */

    /* --- Constructor --- */

    /** 
    *  @brief Constructor (default) - Create an object of the class ClientManagement.
    *  @note  Make sure the vector 'vectorClients' is empty.
    */
     ClientManagement();

    /** 
    *  @brief Desconstructor (default) - Delete all the  object of the vector 'vectorClients'.
    */
    ~ClientManagement();

    /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the vector with all the Clients.
    *  @return 'vectorClients' attribute.
    */
    vector<Client*> getVectorClients() const;

    /** 
    *  @brief  Add a new client.
    *  @param  cli New client to be added.
    *  @return 0 if the client is added successfully | -1 if the parameter is invalid | 1 if the client already exists in the vector
    */
    int clientInsert(Client* cli);
};

class ProductManagement {
private:
    /* ATTRIBUTES */
    vector<Product*> vectorProducts; /** @brief vector with all products. */

public:
    /* METHODS */

    /* --- Constructor --- */

    /** 
    *  @brief Constructor (default) - Create an object of the class ProductManagement.
    *  @note  Make sure the vector 'vectorProducts' is empty.
    */
     ProductManagement();

    /** 
    *  @brief Desconstructor (default) - Delete all the  object of the vector 'vectorProducts'.
    */
    ~ProductManagement();

    /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the vector with all the Products.
    *  @return 'vectorProducts' attribute.
    */
    vector<Product*> getVectorProducts() const;
    

    /** 
    *  @brief  Add a new product.
    *  @param  prod New product to be added.
    *  @return 0 if the product is added successfully | -1 if the parameter is invalid | 1 if the product already exists in the vector
    */
    int productInsert(Product* prod);
};

class WarehouseManagement {
private:
    /* ATTRIBUTES */
    vector<Warehouse*> vectorWarehouses; /** @brief vector with all warehouses. */

public:
    /* METHODS */

    /* --- Constructor --- */

    /** 
    *  @brief Constructor (default) - Create an object of the class WarehouseManagement.
    *  @note  Make sure the list 'vectorWarehouses' is empty.
    */
     WarehouseManagement();

    /** 
    *  @brief Desconstructor (default) - Delete all the  object of the vector 'vectorWarehouses'.
    */
    ~WarehouseManagement();

    /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the vector with all the Warehouse.
    *  @return 'vectorWarehouses' attribute.
    */
    vector<Warehouse*> getVectorWarehouses() const;

     /* --- Other Methods --- */

    /** 
    *  @brief  Add a new warehouse.
    *  @param  prod New warehouse to be added.
    *  @return 0 if the warehouse is added successfully | -1 if the parameter is invalid | 1 if the warehouse already exists in the vector
    */
    int warehouseInsert(Warehouse* ware); 

  
    /** 
    *  @brief  List with the name of the city of the warehouses wiht a give product.
    *  @param  productId  product.
    *  @return vector with the name of the warehouses ordered in ascending order
    */ 
    vector<string> WarehouseWihtProduct(int productId);
};



class OrderManagement {
private:
    /* ATTRIBUTES */
    vector<Order*> vectorOrders; /** @brief vector with all orders. */

public:
    /* METHODS */

    /* --- Constructor --- */

    /** 
    *  @brief Constructor (default) - Create an object of the class OrderManagement.
    *  @note  Make sure the list 'vectorOrders' is empty.
    */
     OrderManagement();

    /** 
    *  @brief Desconstructor (default) - Delete all the  object of the vector 'vectorOrders'.
    */
    ~OrderManagement();

    /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the vector with all the Orders.
    *  @return 'vectorOrders' attribute.
    */
    vector<Order*> getVectorOrders() const;

     /* --- Other Methods --- */

    /** 
    *  @brief  Add a new warehouse.
    *  @param  prod New warehouse to be added.
    *  @return 0 if the warehouse is added successfully | -1 if the parameter is invalid | 1 if the warehouse already exists in the vector
    */
    int orderInsert(Order* ord); 

    /** 
    *  @brief  Update the orders in the vector of the orders and in the clients by reading a text file.
    *  @param  filename Filename of the text file containing the orders information.
    *  @param  ClManager Object with all the clients in the platform.
    *  @param  PrManager Object with all the products in the platform.
    *  @param  WareManager Object with all the warehouse in the platform.
    *  @return number of orders registed | -1 if an error occurs
    *  @note   Each line of the file contains the required information in the following format: OrderId;ClientId;warehouseId;date;product1Id;quant1;product2Id;quant2…
    *  @note   Other functions implemented in this library can be used to implement this method.
    *  @note   Check:
    *  @note    -> client exists  : NO  -ignore this line | YES - update the vector
    *  @note    -> warehouse exists: NO  - ignore this line | YES - update the vetor
    *  @note    -> product exists: NO  - only ignore this product not ignore this line
    */ 
    int updateOrders(string filename, ClientManagement& ClManager, ProductManagement& PrManager, WarehouseManagement& WareManager);


};
class Shipment {
private:
    int shipmentId; /** @brief Unique identifier for the shipment. */
    Order* order;   /** @brief Pointer to the order associated with the shipment. */
    string status;  /** @brief Status of the shipment. (pending, delivered, returned)*/        
    string dispatchDate; /** @brief Date when the shipment was dispatched. */
    string deliveryDate; /** @brief Date when the shipment was delivered. */

public:
       /* METHODS */

    /* --- Constructor --- */
    /** 
    *  @brief Shipment (parameterized) - Create an object of the class Shipment.
    *  @param id Shipment Id.
    *  @param ord pointer to order.
    *  @param st Status of the shipment.
    *  @param dd Dispatch date of the shipment.
    *  @param deld Delivery date of the shipment.
    *  @note  Initialize each attribute with the corresponding argument.
     */ 
    Shipment(int id, Order* ord, string st, string dd, string deld); 

     /* --- Get Methods --- */
     
     /** 
    *  @brief  Get the shipment's shipmentId.
    *  @return 'shipmentId' attribute.
    */
    int getId() const;
    /**
    *  @brief  Get the shipment's order.
    *  @return 'order' attribute.
    */
    Order* getOrder() const;
    /**
    *  @brief  Get the shipment's status.
    *  @return 'status' attribute.
    */
    string getStatus() const;
    /**
    *  @brief  Get the shipment's dispatch date.
    *  @return 'dispatchDate' attribute.
    */
    string getDispatchDate() const;
    /**
    *  @brief  Get the shipment's delivery date.
    *  @return 'deliveryDate' attribute.
    */
    string getDeliveryDate() const;
};

class ShipmentManagement {
private:
    list<Shipment*> listShipments;/*brief List of all shipments */
    queue<Order*> queuePendingOrders; /*brief Queue of pending orders */
    stack<string> stackOperations; /*brief Stack of stock operations (e.g., "ADD to warehouse X product Y with Z", "REMOVE from warehouse X product Y with Z") */

public:
        /* METHODS */
    /* --- Constructor --- */

    /** 
    *  @brief Constructor (default) - Create an object of the class ShipmentManagement.
    *  @note  Make sure the list 'listShipments', the queue 'queuePendingOrders' and the stack 'stackOperations' are empty.
    */
    ShipmentManagement();
    /** 
    *  @brief Desconstructor (default) - Delete all the  object of the list 'listShipments', the queue 'queuePendingOrders' and the stack 'stackOperations'.
    */
    ~ShipmentManagement();
    /* --- Get Methods --- */
            
    /**   
     * @brief  Get the list with all the Shipments.
     * @return 'listShipments' attribute.
     */
    list<Shipment*> getListShipments() const;
    /**
     * @brief  Get the queue with all the pending orders.
     * @return 'queuePendingOrders' attribute.
     */
    queue<Order*> getPendingOrders() const;
    /**
     * @brief  Get the stack with all the stock operations.
     * @return 'stackOperations' attribute.
     */
    stack<string> getStackOperations() const;
        /* --- Other Methods --- */

    /** 
    *  @brief  Add a new shipment.
    *  @param  ship New shipment to be added.
    *  @return 0 if the shipment is added successfully | -1 if the parameter is invalid | 1 if the shipment already exists in the list
    */      
    int shipmentInsert(Shipment* ship);

    /**
     * @brief   Add a new pending order to the queue of pending orders.     
     * @param ord New order to be added to the queue of pending orders.
     * @return 0 if the order is added successfully | -1 if the parameter is invalid | 1 if the order already exists in the queue
     * @note   An order is considered pending if it has been placed but not yet dispatched.
     */
    int addPendingOrder(Order* ord);

    /**
    * @brief   Add a new stock operation to the stack of stock operations.
    * @param op Description of the stock operation to be added to the stack.
    * @return void
    * @note   Stock operations can include actions such as adding or removing products from warehouses, updating product quantities, etc.
    */
    void addStockOperation(string op);


    /*  @brief  Count the number of orders in the queue of pending orders that have at least a product with a quantity greater than or equal to a given value.
    *  @param  minProducts Minimum quantity of products to be considered.
    *  @return Number of orders in the queue of pending orders that have at least a product with a quantity greater than or equal to 'minProducts'.
    */
    int numberOrdersInQueue(int minProducts);

    /*  @brief  Count the number of shipments with a status of "delivered" that were delivered on a specific date.
    *  @param  date Date to be checked (format: "DD-MM-YYYY").
    *  @return Number of shipments with a status of "delivered" that were delivered on the specified date.
    */
    int numberDeliveredOnDate(string date);

  

    /*  @brief  Update the shipments in the list of shipments by reading a text file.
    *  @param  filename Name of the text file to read.
    *  @param  OrdManager Reference to the order management object.
    *  @return 0 if the shipments are updated successfully | -1 if the parameter is invalid.
    */
    int uploadShipments(string filename, OrderManagement& OrdManager);
    
    /*  @brief  Undo the last stock operation performed by popping the last operation from the stack of stock operations and reversing its effect on the warehouses and products.
    *  @param  WareManager Reference to the warehouse management object.
    *  @param  PrManager Reference to the product management object.
    *  @return 0 if the last stock operation is undone successfully | -1 if the stack of stock operations is empty or if an error occurs while undoing the operation.
    *  @note   The function should parse the description of the last stock operation to determine what action was
    *  @note  if the last operation was "ADD to warehouse X product Y with Z", the function should remove product Y from warehouse X with quantity Z. if the last operation was "REMOVE from warehouse X product Y with Z", the function should add product Y to warehouse X with quantity Z.
    */
    int undoLastStockOperation(WarehouseManagement& WareManager, ProductManagement& PrManager);
/*  @brief  Identify the most returned product based on the shipments with a status of "returned" in the list of shipments.
    *  @param  num Reference to an integer where the function will store the number of times the most returned product was returned.
    *  @return Name of the most returned product.
    *  @note   The function should iterate through the list of shipments, count the occurrences of each product in the shipments with a status of "returned", and identify the product that was returned most frequently. If there are multiple products with the same highest return count, the function should return the one that comes first in alphabetical order.
    */
    string mostReturnedProduct(int &num);
/*  @brief  List the products that are in short supply across all warehouses.
    *  @param  WareManager Reference to the warehouse management object.
    *  @return vector with the name of the products ordered in ascending order
    * @note   A product is considered to be in short supply if the total quantity available across all warehouses is less than the total quantity required by the pending orders in the queue of pending orders. 
    * The function should iterate through the queue of pending orders, calculate the total quantity required for each product, and compare it with the total quantity available across all warehouses to determine which products are in short supply.
    */
    vector<string> productsWithNotEnoughStock(WarehouseManagement& WareManager) ;

};
#endif