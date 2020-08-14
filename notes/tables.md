# Table Templates

## CREATE employees
```sql
CREATE TABLE employees(id varchar (32) PRIMARY KEY NOT NULL, first varchar(50), last varchar(50), email varchar(100), address varchar(75), phone varchar(50), start timestamptz NOT NULL, gender varchar(6), ethnicity varchar(50), title varchar(50), salary integer NOT NULL);
```
