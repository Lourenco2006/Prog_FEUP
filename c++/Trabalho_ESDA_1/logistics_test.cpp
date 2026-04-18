#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "logistics.hpp"

using namespace std;


int verifica_addComponent(ProductManagement &proManager)
{
    int er = 0;
    Product *prodx=proManager.getVectorProducts()[2];
    int res=prodx->addComponent(1,proManager);


   
    if (res!=0)
    {
        cout << "...verifica_addComponent ( inserir um componente): retorno(="<<res<<") e' diferente do esperado (=0) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_addComponent ( inserir um componente):  retorno =0 (ok)" << endl;
       
        if (prodx->getComponents().size()!=1) {
            cout << "...verifica_addComponent ( inserir um componente): tamanho do vetor(="<<res<<") e' diferente do esperado (=1) (ERRO)"<< endl ;
           er++;
        } else  {
        cout << "...verifica_addComponent ( inserir um componente):  tamanho do vetor =1 (ok)" << endl;
        }
    }
   
    return er;
}


int verifica_displayProductInfo(ProductManagement &proManager)
{
    int er = 0;
    
  
    stringstream ss;
    string str="",strtotal="",str1;
    Product *prodx=proManager.getVectorProducts()[0];
    prodx->displayProductInfo(ss);
    str1="1 | Rato Óptico 6644 | Informática | 7.2 | 1407.8";
    getline(ss,strtotal);
   
    if (!strtotal.empty()) { strtotal.pop_back();}

  if (strtotal!=str1)
    {
        cout << "...verifica_displayProductInfo: Informação do 1º produto- " << endl<< strtotal <<endl << "Devia aparecer:" << endl << str1 << endl;
           er++;
    }
    else
        cout << "...verifica_displayProductInfo: Informação do 1ª produto está correta (ok) "<< endl<< strtotal<<endl;

    return er;
    
}
   


int verifica_ChecktotalWeight(ProductManagement &proManager)
{
     int er = 0;
    Product *prodx=proManager.getVectorProducts()[2];
    prodx->addComponent(2,proManager);
    int res=prodx->ChecktotalWeight(proManager);

    if (res!=1 )
    {
        cout << "...verifica_ChecktotalWeight: OS pesos não são iguais"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_ChecktotalWeight: Os pesos são iguais" << endl;
    }

    return er;
}

int verifica_updateOrders(OrderManagement& OrdManager,ProductManagement& ProManager,ClientManagement& CliManager,WarehouseManagement& WareManager)
{
    int er = 0;
    int res=OrdManager.updateOrders("orders.csv",CliManager, ProManager,WareManager);
   
    if (res!=4)
    {
        cout << "...verifica_updateOrders:  retorno(="<<res<<") e' diferente do esperado (=4) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_updateOrders:  retorno (="<<res<<") (ok)" << endl;
     
               size_t tam=OrdManager.getVectorOrders()[3]->getVectorProducts().size();
             if (tam!=3)
             {
                 cout << "...verifica_updateOrders ( encomenda nº4):  Numero de produtos da encomenda (="<<tam<<") e' diferente do esperado (=3) (ERRO)"<< endl ;
                    er++;
             }
             else 
                 cout << "...verifica_updateOrders  ( encomenda nº4):  Numero de produtos da encomenda (="<<tam<<") (ok)" << endl;     
     
                      
      
    }
    return er;
}


int verifica_WarehouseWihtProduct(WarehouseManagement& wareManager)
{
    int er = 0;
    int n=0;
    vector<string>  res=wareManager.WarehouseWihtProduct(1);
    string strtotal="";
    string str="Braga Setúbal";
    for (size_t i=0;i<res.size();i++) {
            strtotal=strtotal+res[i]+" ";
        }
    if (!strtotal.empty()) strtotal.pop_back();
   if (str!=strtotal)
   {
       cout << "...verifica_WarehouseWihtProduct(produto 1): Lista de armazens (="<<strtotal<<") e' diferente do esperado (="<<str<<") (ERRO)"<< endl;
          er++;
   }
   else
       cout << "...verifica_WarehouseWihtProduct(produto 1): Lista de armazens (="<<strtotal<<") (ok) "<<endl;

    
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
   
    Warehouse* ware;
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



int main()
{

     int errorCount = 0, error;

    cout << "INICIO DOS TESTES MAIS BASICOS\n\n" << endl;
   
    ClientManagement cliManager;
    int a=importClients("clientsSmall.csv",cliManager);
    cout <<"Importou: "<<a<<" clientes "<<endl;

    WarehouseManagement wareManager;
  //  int b=importWarehouses("warehouses.csv",wareManager);
  //  cout <<"Importou: "<<b<<" warehouses "<<endl <<endl;

    ProductManagement ProdManager;
    Product *prod1=new Product(1,"Rato Óptico 6644","Informática",7.2,1407.83);
    Product *prod2=new Product(2,"Colunas Bluetooth 9727","Informática",0.21,1297.53);
    Product *prod3=new Product(3,"Rato e colunas","Informática",10.72,631.16);
     
    ProdManager.productInsert(prod1);
    ProdManager.productInsert(prod2);
    ProdManager.productInsert(prod3);
    
    OrderManagement OrdManager;

    vector<pair<Product*,int>> vpq1;
    pair<Product*,int> p1(prod1,2);
    pair<Product*,int> p2(prod2,4);
    vpq1.push_back(p1);
    vpq1.push_back(p2);
   
    vector<pair<Product*,int>> vpq2;
    pair<Product*,int> p3(prod3,6);
    vpq2.push_back(p3);
    vpq2.push_back(p2);


    Warehouse* ware1=new Warehouse(1,"Braga",vpq1);
    Warehouse* ware2=new Warehouse(2,"Setúbal",vpq1);
    Warehouse* ware3=new Warehouse(1,"Porto");
    Warehouse* ware4=new Warehouse(1,"Lisboa",vpq2);

    wareManager.warehouseInsert(ware1);
    wareManager.warehouseInsert(ware2);
    wareManager.warehouseInsert(ware3);
    wareManager.warehouseInsert(ware4);

    error = verifica_addComponent(ProdManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_addComponent\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_addComponent passou\n\n" << endl;
    } 

    error = verifica_displayProductInfo(ProdManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_displayProductInfo\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_displayProductInfo passou\n\n" << endl;
    }  
   
    cout << "O seguinte teste depende da função addcomponent estar corretamente implementada" <<endl;
    error = verifica_ChecktotalWeight(ProdManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_ChecktotalWeight\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_ChecktotalWeight passou\n\n" << endl;
    } 

   
    error = verifica_updateOrders(OrdManager,ProdManager,cliManager,wareManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_updateOrders\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_updateOrders passou\n\n" << endl;
    } 

 
   
    error = verifica_WarehouseWihtProduct(wareManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_WarehouseWihtProduct\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_WarehouseWihtProduct passou\n\n" << endl;
    } 


     if (errorCount == 0)
        cout << "FIM DOS TESTES: Todos os testes passaram\n" << endl;
    else
        cout << "FIM DOS TESTES: Foram encontrados "<< errorCount << " ERROS no total\n" << endl;

    return 0;
}

