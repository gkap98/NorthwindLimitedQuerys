//
//  main.cpp
//  trial
//
//  Created by Gavin Kaepernick on 10/31/19.
//  Copyright © 2019 Gavin Kaepernick. All rights reserved.
//

#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

void query1(sqlite3 * db) 	{
	cout << endl;
	cout << "How many customers are in the UK, USA, and Spain?" << endl;
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT count(Customers.CustomerID) FROM Customers WHERE Customers.Country = 'USA' OR Customers.Country = 'UK' OR Customers.Country = 'Spain'", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		sqlite3_step(myStatement);
		int query = sqlite3_column_int(myStatement, 0);
		cout << "	" << query << endl;
		cout << endl << "SELECT count(Customers.CustomerID)" << endl << "FROM Customers" << endl << "WHERE Customers.Country = 'USA'" << endl << "OR Customers.Country = 'UK'" << endl << "OR Customers.Country = 'Spain'" << endl << endl;;
	}
	sqlite3_finalize(myStatement);
}
void query2(sqlite3 * db) 	{
	cout << endl;
	cout << "What are the names and phone numbers of suppliers who are in the 514 area code?" << endl;
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Suppliers.ContactName, Suppliers.Phone FROM Suppliers WHERE Suppliers.Phone LIKE '%(514)%'", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);
		while (statusOfStep == SQLITE_ROW) {
			string query = (char*)sqlite3_column_text(myStatement, 0);
			cout << "	" << query << endl;
			statusOfStep = sqlite3_step(myStatement);
		}
		cout << endl << "SELECT Suppliers.ContactName" << endl << "FROM Suppliers" << endl << "WHERE Suppliers.Phone LIKE '%(514)%'" << endl << endl;
	}
	sqlite3_finalize(myStatement);
}
void query3(sqlite3 * db) 	{
	cout << endl;
	cout << "How many products have a greater value of in-stock items compared to the value of items on order?" << endl;
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT count(ProductName) FROM Products WHERE UnitsInStock > UnitsOnOrder", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);
		while (statusOfStep == SQLITE_ROW) {
			int query = sqlite3_column_int(myStatement, 0);
			cout << "	" << query << endl;
			statusOfStep = sqlite3_step(myStatement);
		}
		cout << endl << "SELECT count(ProductName)" << endl << "FROM Products" << endl << "WHERE UnitsInStock > UnitsOnOrder" << endl << endl;
	}
	sqlite3_finalize(myStatement);
}
void query4(sqlite3 * db) 	{
	cout << endl;
	cout << "What are the names of the products in order #10275?" << endl;
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Products.ProductName FROM [Order Details], Products WHERE [Order Details].OrderID = '10275' AND Products.ProductID = [Order Details].ProductID", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);
		while (statusOfStep == SQLITE_ROW) {
			string query = (char*)sqlite3_column_text(myStatement, 0);
			cout << "	" << query << endl;
			statusOfStep = sqlite3_step(myStatement);
		}
		cout << endl << "SELECT Products.ProductName" << endl << "FROM [Order Details], Products" << endl << "WHERE [Order Details].OrderID = '10275'" << endl << "AND Products.ProductID = [Order Details].ProductID" << endl << endl;
	}
	sqlite3_finalize(myStatement);
}
void query5(sqlite3 * db) 	{
	cout << endl;
	cout << "Who are all the employees who manage others and how many people do they manage?" << endl;
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "WITH Managers AS (SELECT Employees.ReportsTo, count(Employees.ReportsTo) AS SubordinateCount FROM Employees WHERE Employees.ReportsTo IS NOT '' GROUP BY(Employees.ReportsTo)) SELECT Employees.FirstName, Employees.LastName, Managers.SubordinateCount FROM Managers, Employees WHERE Managers.ReportsTo = Employees.EmployeeID;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);
		while (statusOfStep == SQLITE_ROW) {
			string query = (char*)sqlite3_column_text(myStatement, 0);
			cout << "	" << query;
			string query1 = (char*)sqlite3_column_text(myStatement, 1);
			cout << "	" << query1;
			int query2 = sqlite3_column_int(myStatement, 2);
			cout << "	" << query2 << endl;
			statusOfStep = sqlite3_step(myStatement);
		}
		cout << endl << "WITH Managers AS (SELECT Employees.ReportsTo, count(Employees.ReportsTo) AS SubordinateCount" << endl << "FROM Employees" << endl << "WHERE Employees.ReportsTo IS NOT ''" << endl << "GROUP BY(Employees.ReportsTo))" << endl << "SELECT Employees.FirstName, Employees.LastName, Managers.SubordinateCount" << endl << "FROM Managers, Employees" << endl << "WHERE Managers.ReportsTo = Employees.EmployeeID" << endl << endl;
	}
	sqlite3_finalize(myStatement);
}
void query6(sqlite3 * db) 	{
	cout << endl;
	cout << "What are the names of the products that were ever ordered by the customer 'The Big Cheese' in quantities of 10 or more?" << endl;
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Products.ProductName FROM Products, Customers, Orders, [Order Details] WHERE Orders.CustomerID = Customers.CustomerID AND [Order Details].ProductID = Products.ProductID AND Orders.OrderID = [Order Details].OrderID AND Customers.CompanyName = 'The Big Cheese' AND [Order Details].Quantity >= '10'", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);
		while (statusOfStep == SQLITE_ROW) {
			string query = (char*)sqlite3_column_text(myStatement, 0);
			cout << "	" << query << endl;
			statusOfStep = sqlite3_step(myStatement);
		}
		cout << endl << "SELECT Products.ProductName" << endl << "FROM Products, Customers, Orders, [Order Details]" << endl << "WHERE Orders.CustomerID = Customers.CustomerID" << endl << "AND [Order Details].ProductID = Products.ProductID" << endl << "AND Orders.OrderID = [Order Details].OrderID" << endl << "AND Orders.OrderID = [Order Details].OrderID" << endl << "AND [Order Details].Quantity >= '10'" << endl << endl;
	}
	sqlite3_finalize(myStatement);
}
void query7(sqlite3 * db) 	{
	cout << endl;
	cout << "What was the final order price for all items ordered by the customer 'Simons bistro' on January 16th 1997?" << endl;
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT SUM(ALL ([Order Details].UnitPrice * [Order Details].Quantity) * (1 - [Order Details].Discount)) FROM Orders, [Order Details], Customers WHERE Orders.OrderDate LIKE '%1997-01-16%' AND Customers.CompanyName = 'Simons bistro' AND Customers.CustomerID = Orders.CustomerID AND Orders.OrderID = [Order Details].OrderID", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);
		while (statusOfStep == SQLITE_ROW) {
			double query = sqlite3_column_double(myStatement, 0);
			cout << "	" << query << endl;
			statusOfStep = sqlite3_step(myStatement);
		}
		cout << endl << "SUM(ALL ([Order Details].UnitPrice * [Order Details].Quantity) * (1 - [Order Details].Discount))" << endl << "FROM Orders, [Order Details], Customers" << endl << "WHERE Orders.OrderDate LIKE '%1997-01-16%'" << endl << "AND Customers.CompanyName = 'Simons bistro'" << endl << "AND Customers.CustomerID = Orders.CustomerID" << endl << "AND Orders.OrderID = [Order Details].OrderID" << endl << endl;
	}
	sqlite3_finalize(myStatement);
}
void query8(sqlite3 * db) 	{
	cout << endl;
	cout << "Which product that was ever sold at a discount of 25% or more has the most units in stock (and how many units are in stock)?" << endl;
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Products.ProductName, max(Products.UnitsInStock) FROM Products, [Order Details] WHERE Products.ProductID = [Order Details].ProductID AND [Order Details].Discount = .25;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);
		while (statusOfStep == SQLITE_ROW) {
			string query = (char*)sqlite3_column_text(myStatement, 0);
			cout << "	" << query;
			int query1 = sqlite3_column_int(myStatement, 1);
			cout << "	" << query1 << endl;
			statusOfStep = sqlite3_step(myStatement);
		}
		cout << endl << "SELECT Products.ProductName, max(Products.UnitsInStock)" << endl << "FROM Products, [Order Details]" << endl << "WHERE Products.ProductID = [Order Details].ProductID" << endl << "AND [Order Details].Discount = .25" << endl << endl;
	}
	sqlite3_finalize(myStatement);
}
void query9(sqlite3 * db) 	{
	cout << endl;
	cout << "What is the name of the company that had the largest discount on any order, how much was that discount, how much did the company pay minus the discount, and how much would they have paid without the discount?" << endl;
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Customers.CompanyName, SUM('Order Details'.Discount * 'Order Details'.UnitPrice * 'Order Details'.Quantity) AS DiscountAmount, SUM((1 - 'Order Details'.Discount) * 'Order Details'.UnitPrice * 'Order Details'.Quantity) AS PricePaid, SUM('Order Details'.UnitPrice * 'Order Details'.Quantity) AS PriceWithoutDiscount FROM Customers, 'Order Details', Orders WHERE Orders.OrderID = 'Order Details'.OrderID AND Orders.CustomerID = Customers.CustomerID GROUP BY Orders.OrderID ORDER BY DiscountAmount DESC LIMIT 1;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);
		while (statusOfStep == SQLITE_ROW) {
			string name = (char*)sqlite3_column_text(myStatement, 0);
			cout << "	" << name << ",";
			double discountAmount = sqlite3_column_double(myStatement, 1);
			cout << "	" << discountAmount << ",";
			double pricePaid = sqlite3_column_double(myStatement, 2);
			cout << "	" << pricePaid << ",";
			double priceWithoutDiscount = sqlite3_column_double(myStatement, 3);
			cout << "	" << priceWithoutDiscount << endl;
			statusOfStep = sqlite3_step(myStatement);
		}
		cout << endl << "SELECT Customers.CompanyName, SUM('Order Details'.Discount * 'Order Details'.UnitPrice * 'Order Details'.Quantity) AS DiscountAmount, SUM((1 - 'Order Details'.Discount) * 'Order Details'.UnitPrice * 'Order Details'.Quantity) AS PricePaid, SUM('Order Details'.UnitPrice * 'Order Details'.Quantity) AS PriceWithoutDiscount" << endl << "FROM Customers, 'Order Details', Orders" << endl << "WHERE Orders.OrderID = 'Order Details'.OrderI" << endl << "AND Orders.CustomerID = Customers.CustomerID" << endl << "GROUP BY Orders.OrderID" << endl << "ORDER BY DiscountAmount DESC LIMIT 1;" << endl;
	}
	sqlite3_finalize(myStatement);
}
void query10(sqlite3 * db) 	{
	cout << endl;
	cout << "Who are the suppliers whose products have 100 units or more on order." << endl;
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Suppliers.CompanyName FROM Suppliers, Products WHERE Products.SupplierID = Suppliers.SupplierID AND Products.UnitsOnOrder >= 100;", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);
		while (statusOfStep == SQLITE_ROW) {
			string query = (char*)sqlite3_column_text(myStatement, 0);
			cout << "	" << query << endl;
			statusOfStep = sqlite3_step(myStatement);
		}
		cout << endl << "SELECT Suppliers.CompanyName" << endl << "FROM Suppliers, Products" << endl << "WHERE Products.SupplierID = Suppliers.SupplierID" << endl << "AND Products.UnitsOnOrder >= 100;" << endl << endl;
	}
	sqlite3_finalize(myStatement);
}

//-- MAIN

int main()
{
    sqlite3 *db;
	//-- This is just the file name because of Xcode
	//-- 	but you should just be able to change the string to your path
    int statusOfOpen = sqlite3_open("NorthwindLimited.sqlite", &db);

    if (statusOfOpen == SQLITE_OK)
    {
        cout << "Successfully opened the database" << endl;
		int menuChoice = 0;
		
		while (menuChoice != -1) {
			cout << "-----------------" << endl;
			cout << "Main Menu" << endl;
			cout << "-----------------" << endl;
			cout << "1.  Query 1" << endl;
			cout << "2.  Query 2" << endl;
			cout << "3.  Query 3" << endl;
			cout << "4.  Query 4" << endl;
			cout << "5.  Query 5" << endl;
			cout << "6.  Query 6" << endl;
			cout << "7.  Query 7" << endl;
			cout << "8.  Query 8" << endl;
			cout << "9.  Query 9" << endl;
			cout << "10. Query 10" << endl;
			cout << "------------------" << endl;
			
			cout << "Choose a query to execute (-1 to quit) >--> ";
			cin >> menuChoice;
			if (menuChoice == 0 || menuChoice > 10 || menuChoice < -1) {
				cout << endl;
				cout << "Please enter number between 1-10 or -1 to quit" << endl;
				cout << "Choose a query to execute (-1 to quit) >--> ";
				cin >> menuChoice;
			}
			if (menuChoice == 1)
				query1(db);
			if (menuChoice == 2)
				query2(db);
			if (menuChoice == 3)
				query3(db);
			if (menuChoice == 4)
				query4(db);
			if (menuChoice == 5)
				query5(db);
			if (menuChoice == 6)
				query6(db);
			if (menuChoice == 7)
				query7(db);
			if (menuChoice == 8)
				query8(db);
			if (menuChoice == 9)
				query9(db);
			if (menuChoice == 10)
				query10(db);
			cout << endl;
		}
		
	}

    sqlite3_close(db);
	cout << "<< Program Terminated >>" << endl;
    return 0;
}
