#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <list>
#include <queue>
#include <stack>
#include "logistics.hpp"

using namespace std;


int verifica_numberOrdersInQueue(ShipmentManagement &ShipManager)
{
    int er = 0;
    int res=ShipManager.numberOrdersInQueue(2);


   
    if (res!=2)
    {
        cout << "...verifica_numberOrdersInQueue ( minimo de 2 produtos): retorno(="<<res<<") e' diferente do esperado (=2) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_numberOrdersInQueue ( minimo de 2 produtos):  retorno = "<<res<<" (ok)" << endl;
       
   
    }
   
    return er;
}


int verifica_numberDeliveredOnDate(ShipmentManagement &ShipManager)
{
    int er = 0;
    
  
  int res=ShipManager.numberDeliveredOnDate("08-01-2026");
   
    

  if (res!=4)
    {
        cout << "...verifica_numberDeliveredOnDate: Numero de Produtos entregues em 08-01-2006 ="<<res<<" e' diferente do esperado (=4) (ERRO)"<< endl ;
        er++;
    }
    else
        cout << "...verifica_numberDeliveredOnDate: Numero de Produtos entregues em 08-01-2006 ="<< res<<" (ok)" << endl;

    return er;
    
}
   


int verifica_mostReturnedProduct(ShipmentManagement &ShipManager)
{
    int er = 0;
    int num=0;
    string res=ShipManager.mostReturnedProduct(num);

    if (res!="Colunas Bluetooth 9727" )
    {
        cout << "...verifica_mostReturnedProduct: o produto mais devolvido foi ="<< res <<" e' diferente do esperado (=Colunas Bluetooth 9727) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_mostReturnedProduct: o produto mais devolvido foi ="<< res <<" (ok)" << endl;
    }
    if (num != 14)
    {
        cout << "...verifica_mostReturnedProduct: quantidade do produto "<< res <<" devolvido ="<< num <<" e' diferente do esperado (=14) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_mostReturnedProduct: quantidade do produto "<< res <<" devolvido ="<< num <<" (ok)" << endl;
    }
    return er;
}

int verifica_undoLastStockOperation(ShipmentManagement &ShipManager, WarehouseManagement &WareManager, ProductManagement &ProdManager)
{
    int er = 0;
    int res=ShipManager.undoLastStockOperation(WareManager, ProdManager);
   
    if (res!=00)
    {
        cout << "...verifica_undoLastStockOperation:  retorno(="<<res<<") e' diferente do esperado (=0) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_undoLastStockOperation:  retorno (="<<res<<") (ok)" << endl;
     
       int tam=WareManager.getVectorWarehouses()[0]->getVectorPQ()[0].second;
             if (tam!=6)
             {
                 cout << "...verifica_undoLastStockOperation:  Produto 1 no armazem 1 quantidade (="<<tam<<") e' diferente do esperado (=6) (ERRO)"<< endl ;
                    er++;
             }
             else 
                 cout << "...verifica_undoLastStockOperation: Produto 1 no armazem 1 quantidade  (="<<tam<<") (ok)" << endl;     
     
                      
      
    }
    return er;
}


int verifica_productsWithNotEnoughStock(ShipmentManagement& shipManager, WarehouseManagement& wareManager)
{
    int er = 0;
 
    vector<string>  res=shipManager.productsWithNotEnoughStock(wareManager);
    string strtotal="";
    string str="Colunas Bluetooth 9727";
    for (size_t i=0;i<res.size();i++) {
            strtotal=strtotal+res[i]+" ";
        }
    if (!strtotal.empty()) strtotal.pop_back();
   if (str!=strtotal)
   {
       cout << "...verifica_productsWithNotEnoughStock(produto 1): Lista de produtos (="<<strtotal<<") e' diferente do esperado (="<<str<<") (ERRO)"<< endl;
          er++;
   }
   else
       cout << "...verifica_productsWithNotEnoughStock(produto 1): Lista de produtos (="<<strtotal<<") (ok) "<<endl;

    
    return er;
}


int importClients (string filename, ClientManagement &cliManager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open clients.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    Client* cli;
    stringstream ss;
    int cliI;
    while (getline(file, line)) {
        
        string cliId,nam, ci;
        
            
        ss.clear();
        ss << line; 
        cliId.clear();
        
        getline(ss, cliId, ';');
        cliI=stoi(cliId);
        getline(ss, nam, ';');
        getline(ss, ci, ';');
        
        
     
        cli = new Client(cliI, nam, ci);
       
       cliManager.clientInsert(cli);
        count++;
    }
   
    
    file.close();


    return count;

}

int importProducts (string filename, ProductManagement &prodManager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open products.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    Product* prod;
    stringstream ss;
    int proI,compI;
    float wei,pri;
     string proId,nam, ca, we,pr,comp;
    while (getline(file, line)) {
        
       
         
        ss.clear();
        ss << line; 
              
        getline(ss, proId, ';');
        proI=stoi(proId);
        getline(ss, nam, ';');
        getline(ss, ca, ';');
        getline(ss, we, ';');
        getline(ss, pr, ';');
        wei=stof(we);
        pri=stof(pr);
     
        prod = new Product(proI, nam, ca, wei, pri);
        prodManager.productInsert(prod);
       while(getline(ss, comp, ';')){
            compI=stoi(comp);
            prod->addComponent(compI, prodManager);
        }
        prodManager.productInsert(prod);
        count++;
    }
   
    
    file.close();


    return count;

}

int importWarehouses (string filename, WarehouseManagement &WareManager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open warehouse.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    Warehouse* ware;
    stringstream ss;
    int wareI;
    while (getline(file, line)) {
        
        string wareId,ci;
        
            
        ss.clear();
        ss << line; 
        wareId.clear();
        
        getline(ss, wareId, ';');
        wareI=stoi(wareId);
        getline(ss, ci, ';');
             
        ware = new Warehouse(wareI, ci);
        WareManager.warehouseInsert(ware);
        count++;
    }
   
    
    file.close();


    return count;

}


int importWarehouses_stock (string filename, WarehouseManagement &WareManager, ProductManagement &ProdManager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open warehouse_stock.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
 
    stringstream ss;
    vector<Warehouse*> vectorWarehouses=WareManager.getVectorWarehouses();
    int wareI,prodI,quant;
    while (getline(file, line)) {
        
        string wareId,prod,quan;
        
            
        ss.clear();
        ss << line; 
        wareId.clear();
        
        getline(ss, wareId, ';');
        wareI=stoi(wareId);
        getline(ss, prod, ';');
        getline(ss, quan, ';');
        prodI=stoi(prod);
        quant=stoi(quan);
             
        for (Warehouse* ware: vectorWarehouses){
            if (wareI==ware->getId()){
                ware->addProduct(prodI,quant, ProdManager);
                count++;
            }
        }
        
    }
   
    
    file.close();


    return count;

}


int importShipments (string filename,ShipmentManagement &ShipManager, OrderManagement &OrderManager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to openshipments_realistic.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    vector<Order*> VO=OrderManager.getVectorOrders();
    stringstream ss;
     Order* ord1=nullptr;
     bool existOrder=false;
   int shI,ordI;
    while (getline(file, line)) {
        
        string shId,ord,sta,diDate,deDate;
        
            
        ss.clear();
        ss << line; 
        
        
        getline(ss, shId, ';');
        shI=stoi(shId);
        getline(ss, ord, ';');
        ordI=stoi(ord);
        getline(ss, sta, ';');
        getline(ss, diDate, ';');
        getline(ss, deDate, ';');
          
        existOrder=false;     
        for (Order* orde: VO){
            if (ordI==orde->getId()){
                existOrder=true;
                ord1=orde;
            }
        }
        if (!existOrder) { continue;}
        Shipment* ship=new Shipment(shI,ord1,sta,diDate,deDate);
        ShipManager.shipmentInsert(ship);
        count++;
    }
   
    
    file.close();


    return count;

}

int main()
{

    int errorCount = 0, error;

    cout << "INICIO DOS TESTES MAIS BASICOS\n\n" << endl;
   
    ClientManagement cliManager;
    int a=importClients("clientsSmall.csv",cliManager);
    cout <<"Importou: "<<a<<" clientes "<<endl;

    WarehouseManagement wareManager;


    ProductManagement ProdManager;
    Product *prod1=new Product(1,"Rato Óptico 6644","Informática",7.2,1407.83);
    Product *prod2=new Product(2,"Colunas Bluetooth 9727","Informática",0.21,1297.53);
    Product *prod3=new Product(3,"Rato e colunas","Informática",10.72,631.16);
     
    ProdManager.productInsert(prod1);
    ProdManager.productInsert(prod2);
    ProdManager.productInsert(prod3);
    
    OrderManagement OrdManager;

    vector<pair<Product*,int>> vpq1;
    pair<Product*,int> p1(prod1,16);
    pair<Product*,int> p2(prod2,4);
    vpq1.push_back(p1);
    vpq1.push_back(p2);
   
    vector<pair<Product*,int>> vpq2;
    pair<Product*,int> p3(prod3,6);
    vpq2.push_back(p3);
    vpq2.push_back(p2);


    Warehouse* ware1=new Warehouse(1,"Braga",vpq1);
    Warehouse* ware2=new Warehouse(2,"Setúbal",vpq1);
    Warehouse* ware3=new Warehouse(3,"Porto");
    Warehouse* ware4=new Warehouse(4,"Lisboa",vpq2);
    wareManager.warehouseInsert(ware1);
    wareManager.warehouseInsert(ware2);
    wareManager.warehouseInsert(ware3);
    wareManager.warehouseInsert(ware4);
    OrdManager.updateOrders("orders.csv",cliManager, ProdManager,wareManager);


    ShipmentManagement ShipManager;
    Shipment* ship1=new Shipment(1,OrdManager.getVectorOrders()[0],"delivered","01-01-2026","08-01-2026");
    Shipment* ship2=new Shipment(2,OrdManager.getVectorOrders()[1],"returned","02-01-2026","06-01-2026");
    Shipment* ship3=new Shipment(3,OrdManager.getVectorOrders()[2],"pending","03-01-2026","07-01-2026");
    Shipment* ship4=new Shipment(4,OrdManager.getVectorOrders()[3],"delivered","04-01-2026","08-01-2026");
    Shipment* ship5=new Shipment(5,OrdManager.getVectorOrders()[4],"delivered","05-01-2026","08-01-2026");
    Shipment* ship6=new Shipment(6,OrdManager.getVectorOrders()[5],"delivered","06-01-2026","08-01-2026");
Shipment* ship7=new Shipment(7,OrdManager.getVectorOrders()[6],"pending","06-01-2026","08-01-2026");

   
    ShipManager.shipmentInsert(ship1);
    ShipManager.shipmentInsert(ship2);
    ShipManager.shipmentInsert(ship3);
    ShipManager.shipmentInsert(ship4);
    ShipManager.shipmentInsert(ship5);
    ShipManager.shipmentInsert(ship6);
      ShipManager.shipmentInsert(ship7);

    ShipManager.addPendingOrder(OrdManager.getVectorOrders()[0]);
    ShipManager.addPendingOrder(OrdManager.getVectorOrders()[1]);
    ShipManager.addPendingOrder(OrdManager.getVectorOrders()[2]);
    ShipManager.addPendingOrder(OrdManager.getVectorOrders()[3]);

    ShipManager.addStockOperation("ADD to warehouse 1 product 1 with 10");
   
    


    error = verifica_numberOrdersInQueue(ShipManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_numberOrdersInQueue\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_numberOrdersInQueue passou\n\n" << endl;
    } 

    error = verifica_numberDeliveredOnDate(ShipManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_numberDeliveredOnDate\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_numberDeliveredOnDate passou\n\n" << endl;
    }  
   

    error = verifica_mostReturnedProduct(ShipManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_mostReturnedProduct\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_mostReturnedProduct passou\n\n" << endl;
    } 

    error = verifica_undoLastStockOperation(ShipManager, wareManager, ProdManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_undoLastStockOperation\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_undoLastStockOperation passou\n\n" << endl;
    } 

   
     error = verifica_productsWithNotEnoughStock(ShipManager, wareManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_productsWithNotEnoughStock\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_productsWithNotEnoughStock passou\n\n" << endl;
    } 


     if (errorCount == 0)
        cout << "FIM DOS TESTES: Todos os testes passaram\n" << endl;
    else
        cout << "FIM DOS TESTES: Foram encontrados "<< errorCount << " ERROS no total\n" << endl;

    return 0;
}

