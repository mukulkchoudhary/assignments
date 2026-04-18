-- ============================================================================
-- SETUP SCRIPT: Table Alterations & Required Data Insertions
-- Run this entire script once before executing the main queries
-- ============================================================================

-- ============================================================================
-- PART 1: TABLE ALTERATIONS
-- ============================================================================

-- For DAY 6 Q3: Add location_id column to Departmm table
ALTER TABLE Departmm ADD (location_id NUMBER);

-- Update location_id values based on location names
UPDATE Departmm SET location_id = 1700 WHERE location_namemm = 'New York';
UPDATE Departmm SET location_id = 1800 WHERE location_namemm = 'London';
UPDATE Departmm SET location_id = 1900 WHERE location_namemm = 'Tokyo';
UPDATE Departmm SET location_id = 2000 WHERE location_namemm = 'Geneva';
UPDATE Departmm SET location_id = 2100 WHERE location_namemm = 'San Francisco';
UPDATE Departmm SET location_id = 2200 WHERE location_namemm = 'Munich';
UPDATE Departmm SET location_id = 2300 WHERE location_namemm = 'Toronto';

-- Commit the changes
COMMIT;

-- ============================================================================
-- PART 2: MISSING DATA INSERTIONS
-- ============================================================================

-- 1. Add employee 'Davies' for DAY 5 Q3.b (employees hired after Davies)
INSERT INTO Employ1mm (
    empid1mm, last_namemm, salarymm, address1mm, hire_datemm, 
    job_idmm, manager_idmm, commission_pctmm, dept_id1mm
) VALUES (
    111, 'Davies', 5500, '456 Davies Road', TO_DATE('10-JAN-2023', 'DD-MON-YYYY'), 
    'SA_REP', 101, 0.1, 30
);

-- 2. Add employee in Toronto (Department 80) for DAY 5 HA2.b
-- First, verify department 80 exists and is in Toronto
INSERT INTO Employ1mm (
    empid1mm, last_namemm, salarymm, address1mm, hire_datemm, 
    job_idmm, manager_idmm, commission_pctmm, dept_id1mm
) VALUES (
    112, 'TorontoEmp', 8500, '123 Bay Street, Toronto', TO_DATE('20-FEB-2023', 'DD-MON-YYYY'), 
    'FIN_CLERK', 106, NULL, 80
);

-- 3. Add an employee with 'u' in last name if none exists (for DAY 6 Q2)
-- Note: You already have 'Mukul' but adding another for more data variety
INSERT INTO Employ1mm (
    empid1mm, last_namemm, salarymm, address1mm, hire_datemm, 
    job_idmm, manager_idmm, commission_pctmm, dept_id1mm
) VALUES (
    113, 'Kumar', 7200, '789 University Ave', TO_DATE('05-MAR-2023', 'DD-MON-YYYY'), 
    'IT_PROG', 107, NULL, 30
);

-- 4. Add more employees in Department 50 for DAY 6 HA2 & HA3 (salary comparisons)
-- Department 50 exists? Let's check and add if needed
INSERT INTO Departmm (dept_idmm, dept_namemm, location_namemm, location_id)
VALUES (50, 'Sales', 'New York', 1700);

-- Add employees in department 50
INSERT INTO Employ1mm (
    empid1mm, last_namemm, salarymm, address1mm, hire_datemm, 
    job_idmm, manager_idmm, commission_pctmm, dept_id1mm
) VALUES (
    114, 'LowSalary', 3000, '100 Low St', TO_DATE('01-JAN-2023', 'DD-MON-YYYY'), 
    'SALES_REP', 101, 0.05, 50
);

INSERT INTO Employ1mm (
    empid1mm, last_namemm, salarymm, address1mm, hire_datemm, 
    job_idmm, manager_idmm, commission_pctmm, dept_id1mm
) VALUES (
    115, 'MidSalary', 6000, '200 Mid Ave', TO_DATE('15-JAN-2023', 'DD-MON-YYYY'), 
    'SALES_REP', 101, 0.08, 50
);

INSERT INTO Employ1mm (
    empid1mm, last_namemm, salarymm, address1mm, hire_datemm, 
    job_idmm, manager_idmm, commission_pctmm, dept_id1mm
) VALUES (
    116, 'HighSalary', 12000, '300 High Blvd', TO_DATE('10-FEB-2023', 'DD-MON-YYYY'), 
    'SALES_MGR', 106, 0.15, 50
);

-- 5. Add an employee in Executive department if not exists (for DAY 6 Q5)
-- Executive department should be department 40 based on your data
INSERT INTO Employ1mm (
    empid1mm, last_namemm, salarymm, address1mm, hire_datemm, 
    job_idmm, manager_idmm, commission_pctmm, dept_id1mm
) VALUES (
    117, 'ExecutiveEmp', 25000, '500 Executive Plaza', TO_DATE('01-JAN-2020', 'DD-MON-YYYY'), 
    'EXEC_DIR', NULL, NULL, 40
);

-- 6. Add an employee with 'u' in last name in a different department for variety
INSERT INTO Employ1mm (
    empid1mm, last_namemm, salarymm, address1mm, hire_datemm, 
    job_idmm, manager_idmm, commission_pctmm, dept_id1mm
) VALUES (
    118, 'Hughes', 9500, '600 Hughes Lane', TO_DATE('25-MAR-2023', 'DD-MON-YYYY'), 
    'MK_MGR', 102, NULL, 20
);

-- ============================================================================
-- PART 3: VERIFICATION QUERIES (Optional - Run to check data)
-- ============================================================================

-- Check if all required data exists
SELECT 'Checking required data...' AS "Status" FROM DUAL;

-- Check for Davies
SELECT last_namemm, hire_datemm FROM Employ1mm WHERE last_namemm = 'Davies';

-- Check for Toronto employees
SELECT e.last_namemm, d.location_namemm, d.dept_namemm 
FROM Employ1mm e
JOIN Departmm d ON e.dept_id1mm = d.dept_idmm
WHERE d.location_namemm = 'Toronto';

-- Check for employees with 'u' in name
SELECT last_namemm FROM Employ1mm WHERE LOWER(last_namemm) LIKE '%u%';

-- Check for department 50 employees
SELECT last_namemm, salarymm, dept_id1mm FROM Employ1mm WHERE dept_id1mm = 50;

-- Check for Executive department employees
SELECT e.last_namemm, d.dept_namemm 
FROM Employ1mm e
JOIN Departmm d ON e.dept_id1mm = d.dept_idmm
WHERE d.dept_namemm = 'Executive';

-- Check location_id values
SELECT dept_namemm, location_namemm, location_id FROM Departmm;

-- ============================================================================
-- FINAL COMMIT
-- ============================================================================
COMMIT;

-- ============================================================================
-- SUMMARY OF CHANGES MADE:
-- ============================================================================
-- 1. Added location_id column to Departmm table
-- 2. Updated location_id for all existing departments
-- 3. Added employee 'Davies' (empid: 111)
-- 4. Added employee in Toronto (empid: 112)
-- 5. Added employee 'Kumar' with 'u' in name (empid: 113)
-- 6. Added Department 50 'Sales' if not exists
-- 7. Added 3 employees in department 50 (empids: 114, 115, 116)
-- 8. Added employee in Executive department (empid: 117)
-- 9. Added employee 'Hughes' with 'u' in name (empid: 118)
-- ============================================================================




-- ============================================================================
-- DATABASE: DBMS LAB WORK
-- TABLES: Employ1mm, Departmm
-- ============================================================================

-- ============================================================================
-- DAY 5: Displaying data from multiple tables (Joins)
-- ============================================================================

-- ============================================================================
-- CLASSWORK (DAY 5)
-- ============================================================================

-- Q1.a: Display employee name and department name for employees with 'a' in last name
SELECT e.last_namemm AS "Employee Name", 
       d.dept_namemm AS "Department Name"
FROM Employ1mm e
JOIN Departmm d ON e.dept_id1mm = d.dept_idmm
WHERE e.last_namemm LIKE '%a%';

-- Q1.b: Display employee name, department name, location id and city for employees earning commission
SELECT e.last_namemm AS "Employee Name", 
       d.dept_namemm AS "Department Name", 
       d.dept_idmm AS "Location ID", 
       d.location_namemm AS "City"
FROM Employ1mm e
JOIN Departmm d ON e.dept_id1mm = d.dept_idmm
WHERE e.commission_pctmm IS NOT NULL AND e.commission_pctmm > 0;

-- Q2.a: Display employee and manager details with appropriate labels
SELECT e.last_namemm AS "Employee", 
       e.empid1mm AS "Emp#", 
       m.last_namemm AS "Manager", 
       m.empid1mm AS "Mgr#"
FROM Employ1mm e
LEFT JOIN Employ1mm m ON e.manager_idmm = m.empid1mm;

-- Q2.b: Modified query to include King (no manager) and order by employee number
SELECT e.last_namemm AS "Employee", 
       e.empid1mm AS "Emp#", 
       m.last_namemm AS "Manager", 
       m.empid1mm AS "Mgr#"
FROM Employ1mm e
LEFT JOIN Employ1mm m ON e.manager_idmm = m.empid1mm
ORDER BY e.empid1mm;

-- Q3.a: Display employees who work in same department as a given employee (example: Taylor)
SELECT e1.last_namemm AS "Employee Name", 
       e1.dept_id1mm AS "Department Number", 
       e2.last_namemm AS "Colleague in Same Dept"
FROM Employ1mm e1
JOIN Employ1mm e2 ON e1.dept_id1mm = e2.dept_id1mm
WHERE e1.last_namemm = 'Taylor' AND e1.empid1mm != e2.empid1mm;

-- Q3.b: Display employees hired after a specific employee (example: Taylor)
SELECT last_namemm AS "Employee Name", 
       hire_datemm AS "Hire Date"
FROM Employ1mm
WHERE hire_datemm > (SELECT hire_datemm FROM Employ1mm WHERE last_namemm = 'Taylor');

-- Q4: Display employees hired before their managers
SELECT e.last_namemm AS "Employee Name", 
       e.hire_datemm AS "Employee Hire Date", 
       m.last_namemm AS "Manager Name", 
       m.hire_datemm AS "Manager Hire Date"
FROM Employ1mm e
JOIN Employ1mm m ON e.manager_idmm = m.empid1mm
WHERE e.hire_datemm < m.hire_datemm;

-- ============================================================================
-- HOME ASSIGNMENT (DAY 5)
-- ============================================================================

-- HA1.a: Display last name, department number, and department name for all employees
SELECT e.last_namemm AS "Last Name", 
       e.dept_id1mm AS "Department Number", 
       d.dept_namemm AS "Department Name"
FROM Employ1mm e
JOIN Departmm d ON e.dept_id1mm = d.dept_idmm;

-- HA2.a: Unique listing of all jobs in department 80 with location
SELECT DISTINCT e.job_idmm AS "Job", 
       d.location_namemm AS "Location"
FROM Employ1mm e
JOIN Departmm d ON e.dept_id1mm = d.dept_idmm
WHERE e.dept_id1mm = 80;

-- HA2.b: Display employees who work in Toronto
SELECT e.last_namemm AS "Last Name", 
       e.job_idmm AS "Job", 
       e.dept_id1mm AS "Department Number", 
       d.dept_namemm AS "Department Name"
FROM Employ1mm e
JOIN Departmm d ON e.dept_id1mm = d.dept_idmm
WHERE d.location_namemm = 'Toronto';

-- HA3: Display departments with average salary >= 10000
SELECT d.dept_namemm AS "Department's Name", 
       d.location_namemm AS "Department's Location", 
       COUNT(e.empid1mm) AS "Number of People", 
       ROUND(AVG(e.salarymm), 2) AS "Salary"
FROM Departmm d
JOIN Employ1mm e ON d.dept_idmm = e.dept_id1mm
GROUP BY d.dept_namemm, d.location_namemm
HAVING AVG(e.salarymm) >= 10000;

-- ============================================================================
-- DAY 6: Subqueries & Correlated Subqueries
-- ============================================================================

-- ============================================================================
-- CLASSWORK (DAY 6)
-- ============================================================================

-- Q1: Employees earning more than average salary (sorted by salary ascending)
SELECT empid1mm AS "Employee Number", 
       last_namemm AS "Last Name", 
       salarymm AS "Salary"
FROM Employ1mm
WHERE salarymm > (SELECT AVG(salarymm) FROM Employ1mm)
ORDER BY salarymm ASC;

-- Q2.a: Employees working in department with any employee having 'u' in last name
SELECT empid1mm AS "Employee Number", 
       last_namemm AS "Last Name"
FROM Employ1mm
WHERE dept_id1mm IN (SELECT DISTINCT dept_id1mm 
                     FROM Employ1mm 
                     WHERE LOWER(last_namemm) LIKE '%u%');

-- Q2.b: Employees earning more than average AND in department with 'u' in any employee name
SELECT empid1mm AS "Employee Number", 
       last_namemm AS "Last Name", 
       salarymm AS "Salary"
FROM Employ1mm
WHERE salarymm > (SELECT AVG(salarymm) FROM Employ1mm)
  AND dept_id1mm IN (SELECT DISTINCT dept_id1mm 
                     FROM Employ1mm 
                     WHERE LOWER(last_namemm) LIKE '%u%');

-- Q3: Employees whose department location is 1700 (using 'New York' as equivalent)
SELECT e.last_namemm AS "Name", 
       e.dept_id1mm AS "Department Number", 
       e.job_idmm AS "Job ID"
FROM Employ1mm e
JOIN Departmm d ON e.dept_id1mm = d.dept_idmm
WHERE d.location_namemm = 'New York';

-- Q4: Employees who report to King
SELECT last_namemm AS "Name", 
       salarymm AS "Salary"
FROM Employ1mm
WHERE manager_idmm = (SELECT empid1mm FROM Employ1mm WHERE last_namemm = 'King');

-- Q5: All employees in Executive department
SELECT e.dept_id1mm AS "Department Number", 
       e.last_namemm AS "Name", 
       e.job_idmm AS "Job ID"
FROM Employ1mm e
JOIN Departmm d ON e.dept_id1mm = d.dept_idmm
WHERE d.dept_namemm = 'Executive';

-- Q6: 4th highest paid employee
SELECT last_namemm AS "Name", salarymm AS "Salary"
FROM (
    SELECT last_namemm, salarymm, DENSE_RANK() OVER (ORDER BY salarymm DESC) AS rnk
    FROM Employ1mm
)
WHERE rnk = 4;

-- ============================================================================
-- HOME ASSIGNMENT (DAY 6)
-- ============================================================================

-- HA1: Department with minimum average salary
SELECT d.dept_namemm AS "Department", 
       ROUND(AVG(e.salarymm), 2) AS "Average Salary"
FROM Departmm d
JOIN Employ1mm e ON d.dept_idmm = e.dept_id1mm
GROUP BY d.dept_namemm
HAVING AVG(e.salarymm) = (SELECT MIN(AVG(salarymm)) 
                           FROM Employ1mm 
                           GROUP BY dept_id1mm);

-- HA2: Employees earning more than at least one employee in department 50
SELECT last_namemm AS "Name", 
       salarymm AS "Salary"
FROM Employ1mm
WHERE salarymm > ANY (SELECT salarymm FROM Employ1mm WHERE dept_id1mm = 50);

-- HA3: Employees earning more than all employees in department 50
SELECT last_namemm AS "Name", 
       salarymm AS "Salary"
FROM Employ1mm
WHERE salarymm > ALL (SELECT salarymm FROM Employ1mm WHERE dept_id1mm = 50);

-- ============================================================================
-- END OF ALL QUERIES
-- ============================================================================



-- DAY 6 - Classwork Q3 (Working version with no table changes)
-- Display name, department number, and job id for employees in New York
SELECT e.last_namemm AS "Name", 
       e.dept_id1mm AS "Department Number", 
       e.job_idmm AS "Job ID"
FROM Employ1mm e
JOIN Departmm d ON e.dept_id1mm = d.dept_idmm
WHERE d.location_namemm = 'New York';
