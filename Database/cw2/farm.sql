CREATE DATABASE `farm` /*!40100 DEFAULT CHARACTER SET utf8 */;

-- MySQL dump 10.13  Distrib 5.7.17, for Win64 (x86_64)
--
-- Host: localhost    Database: farm
-- ------------------------------------------------------
-- Server version 5.7.21-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `barn`
--

/*DROP TABLE IF EXISTS `barn`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `farm`.`barn` (
  `BID` char(4) NOT NULL,
  `Capacity` INT(11) NOT NULL,
  `Administrator` char(5) NOT NULL,
  PRIMARY KEY (`BID`),
  FOREIGN KEY (`Administrator`)
  REFERENCES `farm`.`barnadmin` (`AdminID`)
) /*ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;


--
-- Dumping data for table `barn`
--

/*LOCK TABLES `barn` WRITE;
/*!40000 ALTER TABLE `barn` DISABLE KEYS */;
INSERT INTO `farm`.`barn` VALUES ('B001',1200,'A0001'),('B002',1500,'A0002'),('B003',1300,'A0003'),('B004',1300,'A0004'),('B005',800,'A0005'),('B006',900,'A0006');

/*UNLOCK TABLES;

--
-- Table structure for table `barnadmin`
--

DROP TABLE IF EXISTS `barnadmin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `farm`.`barnadmin` (
  `﻿FirstName` VARCHAR(15) NOT NULL,
  `Mid` char(1) DEFAULT NULL,
  `LastName` VARCHAR(15) NOT NULL,
  `AdminID` char(5) NOT NULL,
  `Gender` char(1) NOT NULL,
  `PNumber` BIGINT NOT NULL,
  PRIMARY KEY (`AdminID`)
) /*ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `barnadmin`
--

/*LOCK TABLES `barnadmin` WRITE;
/*!40000 ALTER TABLE `barnadmin` DISABLE KEYS */;
INSERT INTO `farm`.`barnadmin` VALUES ('Kakala','L','Lopez','A0001','F',2199954865),('Audrey','K','Wright','A0002','F',2199964321),('Logan','K','King','A0003','M',2197456321),('Elligh','J','Scott','A0004','M',2191234567),('Diego','H','Allen','A0005','M',2197568423),('Kyle','M','Hill','A0006','M',2191756985);

/*UNLOCK TABLES;

--
-- Table structure for table `crop`
--

DROP TABLE IF EXISTS `crop`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `farm`.`crop` (
  `Cname` VARCHAR(15) NOT NULL,
  `YieldExp` INT(11) DEFAULT NULL,
  `MaxStorageTime` INT(11) DEFAULT NULL,
  `GrowTime` INT(11) DEFAULT NULL,
  `SeedBrand` VARCHAR(15) DEFAULT NULL,
  PRIMARY KEY (`Cname`)
) /*ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `crop`
--

/*LOCK TABLES `crop` WRITE;
/*!40000 ALTER TABLE `crop` DISABLE KEYS */;
INSERT INTO `farm`.`crop` VALUES ('wheat',500,36,8,'Dupout'),('corn',750,24,4,'Mornsanto'),('soybean',170,48,5,'Mornsanto'),('potato',2000,7,2,'syngenta'),('lettuce',1600,1,2,'Seminis'),('tomato',6000,1,4,'Syngenta');

/*UNLOCK TABLES;

--
-- Table structure for table `farmer`
--

DROP TABLE IF EXISTS `farmer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `farm`.`farmer` (
  `﻿Fname` VARCHAR(15) NOT NULL,
  `Minit` char(1) DEFAULT NULL,
  `Lname` VARCHAR(15) NOT NULL,
  `FID` char(5) NOT NULL,
  `Gender` char(1) NOT NULL,
  `Bdate` VARCHAR(10) DEFAULT NULL,
  `PhoneNo` char(10) NOT NULL,
  `LeaderID` char(5) DEFAULT NULL,
  PRIMARY KEY (`FID`),
  FOREIGN KEY (`LeaderID`)
  REFERENCES `farm`.`farmer` (`FID`)

) /*ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `farmer`
--

/*LOCK TABLES `farmer` WRITE;
/*!40000 ALTER TABLE `farmer` DISABLE KEYS */;
INSERT INTO `farm`.`farmer` VALUES ('Emma','L','Davis','F0001','F','1972/3/6','2193456825','null'),('Jacob','M','Bush','F0002','M','1979/3/9','2193546985','F0001'),('James','Y','Smith','F0003','M','1986/1/16','2193549646','F0002'),('Aidan','I','Johnson','F0004','M','1978/6/7','2191354899','F0001'),('Chase','I','Taylor','F0005','M','1990/7/4','2196665849','F0002'),('Liam','O','Williams','F0006','M','1987/8/12','2193333333','F0004'),('Alex','P','Martin','F0007','M','1989/2/18','2199999999','F0002'),('Zoe','P','Thompson','F0008','F','1992/9/18','2195465854','F0004'),('Rachel','T','Brown','F0009','F','1989/9/7','2197777777','F0002');

/*UNLOCK TABLES;

--
-- Table structure for table `farmland`
--

DROP TABLE IF EXISTS `farmland`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `farm`.`farmland` (
  `LID` CHAR(4) NOT NULL,
  `Area` INT(11) NOT NULL,
  `Soil` VARCHAR(20) NULL,
  `FarmerID` CHAR(5) NOT NULL,
  PRIMARY KEY (`LID`),
  FOREIGN KEY (`FarmerID`)
  REFERENCES `farm`.`farmer` (`FID`)

) /*ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `farmland`
--

/*LOCK TABLES `farmland` WRITE;
/*!40000 ALTER TABLE `farmland` DISABLE KEYS */;
INSERT INTO `farm`.`farmland` VALUES ('L001',60,'Cinnamon soil','F0001'),('L002',150,'Red soil','F0002'),('L003',58,'Red soil','F0003'),('L004',57,'Cinnamon soil','F0004'),('L005',60,'Red soil','F0005'),('L006',180,'Red soil','F0006'),('L007',166,'Black soil','F0007'),('L008',58,'Cinnamon soil','F0008'),('L009',60,'Black soil','F0009'),('L010',10,'Red soil','F0005'),('L011',15,'Cinnamon soil','F0009'),('L012',19,'Cinnamon soil','F0008'),('L013',59,'Red soil','F0006'),('L014',57,'Cinnamon soil','F0007'),('L015',62,'Black soil','F0003');

/*UNLOCK TABLES;

--
-- Table structure for table `plan`
--

DROP TABLE IF EXISTS `plan`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `farm`.`plan` (
  `LandID` CHAR(4) NOT NULL,
  `CropName` VARCHAR(20) NOT NULL,
  `Fertilizer` VARCHAR(20) NULL,
  `TimeOfYear` VARCHAR(20) NOT NULL,
  PRIMARY KEY (`LandID`, `CropName`),
  FOREIGN KEY (`LandID`)
  REFERENCES `farm`.`farmland` (`LID`),
  FOREIGN KEY (`CropName`)
  REFERENCES `farm`.`crop` (`Cname`)
) /*ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;


--
-- Dumping data for table `plan`
--

/*LOCK TABLES `plan` WRITE;
/*!40000 ALTER TABLE `plan` DISABLE KEYS */;
INSERT INTO `farm`.`plan` VALUES ('L001','wheat','NPK','first half year'),('L002','corn','Single nutrient','second half year'),('L003','soybean','NP','full year'),('L004','potato','NK','full year'),('L005','lettuce','PK','full year'),('L006','tomato','Micronutrients','full year'),('L007','wheat','NPK','first half year'),('L008','corn','Single nutrient','second half year'),('L009','soybean','NP','full year'),('L010','potato','NK','full year'),('L011','lettuce','PK','full year'),('L012','tomato','Micronutrients','full year'),('L013','wheat','NPK','first half year'),('L014','corn','Single nutrient','second half year'),('L015','soybean','NP','full year'),('L001','corn','Single nutrient','second half year'),('L002','wheat','NPK','first half year'),('L007','corn','Single nutrient','second half year'),('L008','wheat','NPK','first half year'),('L013','corn','Single nutrient','second half year'),('L014','wheat','NPK','first half year'),('','','','');

/*UNLOCK TABLES;

--
-- Table structure for table `purchase`
--

DROP TABLE IF EXISTS `purchase`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `farm`.`purchase` (
  `Purchaser` VARCHAR(15) NOT NULL,
  `Crop` VARCHAR(15) NOT NULL,
  `Quantity` INT(11) NULL,
  `UnitPrice` DECIMAL(3,1) NULL,
  PRIMARY KEY (`Purchaser`, `Crop`),
  FOREIGN KEY (`Purchaser`)
  REFERENCES `farm`.`purchaser` (`Company`),
  FOREIGN KEY (`Crop`)
  REFERENCES `farm`.`crop` (`Cname`)

) /*ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `purchase`
--

/*LOCK TABLES `purchase` WRITE;
/*!40000 ALTER TABLE `purchase` DISABLE KEYS */;
INSERT INTO `farm`.`purchase` VALUES ('Walmart','wheat',400,0.4),('Goodhealth','wheat',700,0.3),('godfish','corn',750,0.6),('Mcdonald','potato',1800,0.5),('Subway','Lettuce',1500,0.5),('KFC','tomato',5500,0.2),('Walmart','tomato',4500,0.2),('Goodhealth','corn',600,0.3),('Godfish','soybean',600,0.6),('Mcdonald','Lettuce',1000,0.5),('Subway','tomato',4000,0.2),('KFC','potato',1500,0.5);

/*UNLOCK TABLES;

--
-- Table structure for table `purchaser`
--

DROP TABLE IF EXISTS `purchaser`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `farm`.`purchaser` (
  `Company` VARCHAR(15) NOT NULL,
  `Address` VARCHAR(50) NULL,
  `PhoneNo` CHAR(10) NOT NULL,
  `Contact` VARCHAR(15) NOT NULL,
  `StartOfContact` VARCHAR(10) NOT NULL,
  `EndOfContract` VARCHAR(10) NOT NULL,
  PRIMARY KEY (`Company`)
) /*ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;


--
-- Dumping data for table `purchaser`
--

/*LOCK TABLES `purchaser` WRITE;
/*!40000 ALTER TABLE `purchaser` DISABLE KEYS */;
INSERT INTO `farm`.`purchaser` VALUES ('Walmart','1088  Broadway St IN','2192465874','Mr.Smith','2017/7/6','2030/1/1'),('Goodhealth','1036  Indianapolis IN','2192424565','Mr.Handsome','2017/9/6','2035/6/7'),('Godfish','1153  Berries Summer IN','2193456857','Mr.Mole','2017/3/7','2037/5/9'),('Mcdonald','761  Vose Hometory IN','2193247865','Mr.Nelson','2014/3/9','2034/2/5'),('Subway','986 stone Summer IN','2198562764','Mr.Adam','2018/3/1','2038/9/9'),('KFC','623 Todame Bollaria IN','2199637152','Mr.roberts','2008/6/6','2028/1/1');

/*UNLOCK TABLES;

--
-- Table structure for table `section`
--

DROP TABLE IF EXISTS `section`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `farm`.`section` (
  `﻿BarnID` CHAR(4) NOT NULL,
  `SectionNo` CHAR(4) NOT NULL,
  `CropName` VARCHAR(15) DEFAULT NULL,
  `Temp` INT(11) DEFAULT NULL,
  `Humidity` decimal(3,2) DEFAULT NULL,
  `Stock` INT(11) DEFAULT NULL,
  PRIMARY KEY (`﻿BarnID`,`SectionNo`),
  FOREIGN KEY (`﻿BarnID`)
  REFERENCES `farm`.`barn` (`BID`)
) /*ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `section`
--

/*LOCK TABLES `section` WRITE;
/*!40000 ALTER TABLE `section` DISABLE KEYS */;
INSERT INTO `farm`.`section` VALUES ('B001','S001','wheat',13,0.50,150),('B001','S002','corn',10,0.60,200),('B001','S003','soybean',15,0.60,110),('B002','S001','potato',5,0.60,100),('B002','S002','Lettuce',0,0.50,100),('B003','S001','Lettuce',0,0.50,50),('B003','S002','wheat',13,0.50,150),('B004','S001','potato',5,0.60,130),('B004','S002','lettuce',0,0.50,90),('B004','S003','null',0,0.50,0),('B005','S001','soybean',15,0.60,0),('B005','S002','null',10,0.60,0),('B006','S001','corn',10,0.60,240),('B006','S002','soybean',15,0.60,110);

/*UNLOCK TABLES;

--
-- Dumping routines for database 'farm'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-04-13 23:38:20
