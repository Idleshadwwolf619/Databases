-- Create the database
CREATE DATABASE IF NOT EXISTS Gaming_Company;
USE Gaming_Company;

-- Create ProjectState Table
CREATE TABLE IF NOT EXISTS ProjectState (
    StateID INT PRIMARY KEY,
    Description VARCHAR(255)
);

-- Create JobRole Table
CREATE TABLE IF NOT EXISTS JobRole (
    JobID INT PRIMARY KEY,
    RoleName VARCHAR(255)
);

-- Create Project Table
CREATE TABLE IF NOT EXISTS Project (
    ProjectID INT PRIMARY KEY,
    Name VARCHAR(255),
    LaunchDate DATE,
    StateID INT,
    FOREIGN KEY (StateID) REFERENCES ProjectState(StateID)
);

-- Create Storefront Table
CREATE TABLE IF NOT EXISTS Storefront (
    ProjectID INT PRIMARY KEY,
    InventoryQuantity INT,
    Price DECIMAL(10, 2),
    FOREIGN KEY (ProjectID) REFERENCES Project(ProjectID)
);

-- Create Employee Table
CREATE TABLE IF NOT EXISTS Employee (
    EmployeeID INT PRIMARY KEY,
    FirstName VARCHAR(255),
    LastName VARCHAR(255),
    JobID INT,
    ProjectID INT,
    Cost DECIMAL(10, 2),
    FOREIGN KEY (JobID) REFERENCES JobRole(JobID),
    FOREIGN KEY (ProjectID) REFERENCES Project(ProjectID)
);

-- Create Author Table
CREATE TABLE IF NOT EXISTS Author (
    AuthorID INT PRIMARY KEY,
    FirstName VARCHAR(255),
    LastName VARCHAR(255),
    ProjectID INT,
    FOREIGN KEY (ProjectID) REFERENCES Project(ProjectID)
);

-- Insert example JobRoles
INSERT INTO JobRole (JobID, RoleName) VALUES
(1, 'Game Programmer'),
(2, 'Game Artist'),
(3, 'Game Designer'),
(4, 'Producer'),
(5, 'Tester');

-- Insert example ProjectStates
INSERT INTO ProjectState (StateID, Description) VALUES
(1, 'Development'),
(2, 'Testing'),
(3, 'Release');

-- Insert example Projects with names, states, and budgets
INSERT INTO Project (ProjectID, Name, LaunchDate, StateID) VALUES
(1, 'SuperGame', '2023-01-01', 1),
(2, 'AdventureQuest', '2023-02-01', 2),
(3, 'GalacticEmpire', '2023-03-01', 1),
(4, 'MysteryMansion', '2023-04-01', 3),
(5, 'SpeedRacer', '2023-05-01', 1);

-- Insert example Budget for each project
INSERT INTO Storefront (ProjectID, InventoryQuantity, Price) VALUES
(1, 1000, 49.99),
(2, 800, 39.99),
(3, 1200, 59.99),
(4, 500, 29.99),
(5, 1500, 44.99);

-- Insert additional example Employees with various roles and individual costs
INSERT INTO Employee (EmployeeID, FirstName, LastName, JobID, ProjectID, Cost) VALUES
(1, 'Eva', 'Garcia', 1, 2, 7000),
(2, 'Michael', 'Johnson', 1, 2, 8000),
(3, 'Olivia', 'Lee', 2, 3, 7500),
(4, 'Daniel', 'Miller', 2, 3, 9000),
(5, 'Sophia', 'Taylor', 2, 3, 8500),
(6, 'Andrew', 'Anderson', 3, 4, 7200),
(7, 'Emma', 'Moore', 3, 4, 7800),
(8, 'Liam', 'Wilson', 3, 4, 7000),
(9, 'Ava', 'Brown', 4, 5, 8200),
(10, 'William', 'Jones', 5, 5, 7900),
(11, 'Mia', 'Smith', 5, 5, 7500),
(12, 'James', 'Davis', 5, 5, 8800),
(13, 'Grace', 'Clark', 5, 5, 8300),
(14, 'Logan', 'Hill', 1, 1, 7600),
(15, 'Chloe', 'Baker', 1, 1, 7400);

-- Calculate and display project total revenue, total employee cost, and total balance for each project
SELECT
    p.Name AS ProjectName,
    s.InventoryQuantity,
    s.Price,
    (s.InventoryQuantity * s.Price) AS TotalRevenue,
    SUM(e.Cost) AS TotalEmployeeCost,
    ((s.InventoryQuantity * s.Price) - SUM(e.Cost)) AS TotalBalance
FROM Project p
JOIN Storefront s ON p.ProjectID = s.ProjectID
JOIN Employee e ON p.ProjectID = e.ProjectID
GROUP BY p.ProjectID, s.InventoryQuantity, s.Price;

-- Show all employees and their assigned projects
SELECT
    e.FirstName,
    e.LastName,
    p.Name AS ProjectName
FROM Employee e
JOIN Project p ON e.ProjectID = p.ProjectID;

-- Insert example Authors with individual games for each project
INSERT INTO Author (AuthorID, FirstName, LastName, ProjectID) VALUES
(1, 'Robert', 'Solis', (SELECT ProjectID FROM Project WHERE Name = 'SuperGame')),
(2, 'Robert', 'Solis', (SELECT ProjectID FROM Project WHERE Name = 'AdventureQuest')),
(3, 'Robert', 'Solis', (SELECT ProjectID FROM Project WHERE Name = 'GalacticEmpire')),
(4, 'Robert', 'Solis', (SELECT ProjectID FROM Project WHERE Name = 'MysteryMansion')),
(5, 'Robert', 'Solis', (SELECT ProjectID FROM Project WHERE Name = 'SpeedRacer'));

-- Update inventory quantity and price for each game individually (replace 'SuperGame' with other project names)
UPDATE Storefront SET InventoryQuantity = 100, Price = 49.99 WHERE ProjectID = (SELECT ProjectID FROM Project WHERE Name = 'SuperGame');
-- Repeat the above line for each game, updating InventoryQuantity and Price accordingly


-- Join queries
-- Verify the changes
SELECT
    p.Name AS ProjectName,
    s.InventoryQuantity,
    s.Price,
    (s.InventoryQuantity * s.Price) AS TotalRevenue,
    SUM(e.Cost) AS TotalEmployeeCost,
    ((s.InventoryQuantity * s.Price) - SUM(e.Cost)) AS TotalBalance
FROM Project p
JOIN Storefront s ON p.ProjectID = s.ProjectID
JOIN Employee e ON p.ProjectID = e.ProjectID
GROUP BY p.ProjectID, s.InventoryQuantity, s.Price;

-- Join Project with ProjectState
SELECT Project.Name, Project.LaunchDate, ProjectState.Description
FROM Project
JOIN ProjectState ON Project.StateID = ProjectState.StateID;

-- Join Employee with JobRole
SELECT Employee.FirstName, Employee.LastName, JobRole.RoleName
FROM Employee
JOIN JobRole ON Employee.JobID = JobRole.JobID;

-- Calculate and display the sum of all project revenue after cost
SELECT
    'All Projects' AS ProjectName,
    SUM(s.InventoryQuantity * s.Price) AS TotalRevenue,
    SUM(e.Cost) AS TotalEmployeeCost,
    (SUM(s.InventoryQuantity * s.Price) - SUM(e.Cost)) AS TotalBalance
FROM Project p
JOIN Storefront s ON p.ProjectID = s.ProjectID
JOIN Employee e ON p.ProjectID = e.ProjectID;

-- Display each project's employees along with their costs and roles
SELECT
    p.Name AS ProjectName,
    e.FirstName,
    e.LastName,
    e.Cost AS EmployeeCost,
    j.RoleName
FROM Project p
JOIN Employee e ON p.ProjectID = e.ProjectID
JOIN JobRole j ON e.JobID = j.JobID;

-- Project 1: SuperGame
SELECT
    'SuperGame' AS ProjectName,
    e.FirstName,
    e.LastName,
    e.Cost AS EmployeeCost,
    j.RoleName
FROM Project p
JOIN Employee e ON p.ProjectID = e.ProjectID
JOIN JobRole j ON e.JobID = j.JobID
WHERE p.Name = 'SuperGame';

-- Project 2: AdventureQuest
SELECT
    'AdventureQuest' AS ProjectName,
    e.FirstName,
    e.LastName,
    e.Cost AS EmployeeCost,
    j.RoleName
FROM Project p
JOIN Employee e ON p.ProjectID = e.ProjectID
JOIN JobRole j ON e.JobID = j.JobID
WHERE p.Name = 'AdventureQuest';

-- Project 3: GalacticEmpire
SELECT
    'GalacticEmpire' AS ProjectName,
    e.FirstName,
    e.LastName,
    e.Cost AS EmployeeCost,
    j.RoleName
FROM Project p
JOIN Employee e ON p.ProjectID = e.ProjectID
JOIN JobRole j ON e.JobID = j.JobID
WHERE p.Name = 'GalacticEmpire';

-- Project 4: MysteryMansion
SELECT
    'MysteryMansion' AS ProjectName,
    e.FirstName,
    e.LastName,
    e.Cost AS EmployeeCost,
    j.RoleName
FROM Project p
JOIN Employee e ON p.ProjectID = e.ProjectID
JOIN JobRole j ON e.JobID = j.JobID
WHERE p.Name = 'MysteryMansion';

-- Project 5: SpeedRacer
SELECT
    'SpeedRacer' AS ProjectName,
    e.FirstName,
    e.LastName,
    e.Cost AS EmployeeCost,
    j.RoleName
FROM Project p
JOIN Employee e ON p.ProjectID = e.ProjectID
JOIN JobRole j ON e.JobID = j.JobID
WHERE p.Name = 'SpeedRacer';

-- Show the Author table
SELECT * FROM Author;