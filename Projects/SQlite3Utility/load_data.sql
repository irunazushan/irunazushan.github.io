CREATE TABLE city (
    city_id INT PRIMARY KEY,
    city_name VARCHAR(50),
    delivery_time INT
);

CREATE TABLE customer (
    customer_id INT PRIMARY KEY,
    customer_name VARCHAR(50),
    city_id INT,
    FOREIGN KEY (city_id) REFERENCES city(city_id)
);

CREATE TABLE device_type (
    device_type_id INT PRIMARY KEY,
    type_name VARCHAR(50)
);

CREATE TABLE product (
    product_id INT PRIMARY KEY,
    product_name VARCHAR(50),
    price DECIMAL(10, 2),
    quantity_in_stock INT,
    supplier VARCHAR(50),
    device_type_id INT,
    FOREIGN KEY (device_type_id) REFERENCES device_type(device_type_id)
);

CREATE TABLE warehouse (
    warehouse_id INT PRIMARY KEY,
    rack_name VARCHAR(50),
    product_id INT,
    location_row INT,
    location_column INT,
    FOREIGN KEY (product_id) REFERENCES product(product_id)
);

CREATE TABLE product_location (
    location_id INT PRIMARY KEY,
    warehouse_id INT,
    product_id INT,
    quantity INT,
    FOREIGN KEY (warehouse_id) REFERENCES warehouse(warehouse_id),
    FOREIGN KEY (product_id) REFERENCES product(product_id)
);

CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    customer_id INT,
    FOREIGN KEY (customer_id) REFERENCES customer(customer_id)
);

CREATE TABLE order_details (
    order_details INT AUTO_INCREMENT PRIMARY KEY,
    order_id INT,
    product_id INT,
    amount INT,
    FOREIGN KEY (product_id) REFERENCES product(product_id),
    FOREIGN KEY (order_id) REFERENCES orders(order_id)
);

CREATE TABLE order_stage (
    stage_id INT PRIMARY KEY,
    stage_name VARCHAR(50)
);

CREATE TABLE order_progress (
    progress_id INT AUTO_INCREMENT PRIMARY KEY,
    stage_id INT,
    order_id INT,
    start_time DATETIME,
    end_time DATETIME,
    FOREIGN KEY (stage_id) REFERENCES order_stage(stage_id),
    FOREIGN KEY (order_id) REFERENCES orders(order_id)
);

-- Вношу данные

INSERT INTO city (city_id, city_name, delivery_time) VALUES (1, 'Санкт-Петербург', 4);
INSERT INTO city (city_id, city_name, delivery_time) VALUES (2, 'Екатеринбург', 3);
INSERT INTO city (city_id, city_name, delivery_time) VALUES (3, 'Казань', 5);
INSERT INTO city (city_id, city_name, delivery_time) VALUES (4, 'Волgоград', 12);

INSERT INTO customer (customer_id, customer_name, city_id) VALUES (2, 'Петров Павел', 1);
INSERT INTO customer (customer_id, customer_name, city_id) VALUES (3, 'Иванова Мария', 2);
INSERT INTO customer (customer_id, customer_name, city_id) VALUES (6, 'Смирнов Алексей', 3);
INSERT INTO customer (customer_id, customer_name, city_id) VALUES (7, 'Козлова Ольга', 4);

INSERT INTO device_type (device_type_id, type_name) VALUES (1, 'Ноутбук');
INSERT INTO device_type (device_type_id, type_name) VALUES (2, 'Телевизор');
INSERT INTO device_type (device_type_id, type_name) VALUES (3, 'Телефон');
INSERT INTO device_type (device_type_id, type_name) VALUES (4, 'Системный блок');
INSERT INTO device_type (device_type_id, type_name) VALUES (5, 'Часы');
INSERT INTO device_type (device_type_id, type_name) VALUES (6, 'Микрофон');

INSERT INTO product (product_id, price, product_name,  quantity_in_stock, supplier, device_type_id) VALUES (1, 1000.00, 'Lenovo', 100, 'ООО "ТехноВещь"', 1);
INSERT INTO product (product_id, price,  product_name,  quantity_in_stock, supplier, device_type_id) VALUES (2, 1500.00,'Sony', 130, 'ООО "Электроника"', 2);
INSERT INTO product (product_id, price,  product_name,  quantity_in_stock, supplier, device_type_id) VALUES (3, 500.00, 'Samsung',120, 'ИП "ГаджетМир"', 3);
INSERT INTO product (product_id, price, product_name,   quantity_in_stock, supplier, device_type_id) VALUES (4, 800.00,'Aces', 120, 'ООО "Электроника"', 4);
INSERT INTO product (product_id, price,  product_name,  quantity_in_stock, supplier, device_type_id) VALUES (5, 200.00, 'Casio', 200, 'ИП "ГаджетМир"', 5);
INSERT INTO product (product_id, price,  product_name,  quantity_in_stock, supplier, device_type_id) VALUES (6, 50.00, 'HyperX', 150, 'ООО "ТехноВещь"', 6);

INSERT INTO warehouse (warehouse_id, rack_name, location_row, location_column) VALUES (1, 'Стеллаж А', 2, 4);
INSERT INTO warehouse (warehouse_id, rack_name, location_row, location_column) VALUES (2, 'Стеллаж А', 3, 7);
INSERT INTO warehouse (warehouse_id, rack_name, location_row, location_column) VALUES (3, 'Стеллаж Б', 2, 2);
INSERT INTO warehouse (warehouse_id, rack_name, location_row, location_column) VALUES (4, 'Стеллаж Ж', 4, 5);
INSERT INTO warehouse (warehouse_id, rack_name, location_row, location_column) VALUES (5, 'Стеллаж В', 3, 7);
INSERT INTO warehouse (warehouse_id, rack_name, location_row, location_column) VALUES (6, 'Стеллаж З', 3, 7);

INSERT INTO product_location (location_id, warehouse_id, product_id, quantity) VALUES (1, 1, 1, 25);
INSERT INTO product_location (location_id, warehouse_id, product_id, quantity) VALUES (2, 1, 2, 30);
INSERT INTO product_location (location_id, warehouse_id, product_id, quantity) VALUES (3, 2, 1, 25);
INSERT INTO product_location (location_id, warehouse_id, product_id, quantity) VALUES (4, 3, 3, 25);
INSERT INTO product_location (location_id, warehouse_id, product_id, quantity) VALUES (5, 5, 3, 25);
INSERT INTO product_location (location_id, warehouse_id, product_id, quantity) VALUES (6, 6, 3, 25);
INSERT INTO product_location (location_id, warehouse_id, product_id, quantity) VALUES (7, 4, 4, 15);
INSERT INTO product_location (location_id, warehouse_id, product_id, quantity) VALUES (8, 1, 5 ,20);
INSERT INTO product_location (location_id ,warehouse_id ,product_id ,quantity )VALUES(9 ,4 ,6 ,10);

INSERT INTO orders (order_id, customer_id) VALUES (10, 2);
INSERT INTO orders (order_id, customer_id) VALUES (11, 3);
INSERT INTO orders (order_id, customer_id) VALUES (14, 6);
INSERT INTO orders (order_id, customer_id) VALUES (15, 7);

INSERT INTO order_details (order_id, product_id, amount )VALUES(10, 1, 2);
INSERT INTO order_details (order_id, product_id, amount )VALUES(10 ,3 ,1);
INSERT INTO order_details (order_id, product_id, amount )VALUES(10 ,6 ,1);
INSERT INTO order_details (order_id, product_id, amount )VALUES(11 ,2 ,3);
INSERT INTO order_details (order_id, product_id, amount )VALUES(14 ,1 ,3);
INSERT INTO order_details (order_id, product_id, amount )VALUES(14 ,4 ,1);
INSERT INTO order_details (order_id, product_id, amount )VALUES(15 ,5 ,1);