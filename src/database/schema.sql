-- Création de la base de données
CREATE DATABASE RestaurantManagement;

-- Se connecter à la base de données
\c RestaurantManagement;

-- 1. Création des Tables
-- Table des recettes
CREATE TABLE recipes (
    recipe_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    preparation_time INT NOT NULL, -- en minutes
    cooking_time INT NOT NULL, -- en minutes
    description TEXT NOT NULL
);

-- Table des ingrédients
CREATE TABLE ingredients (
    ingredient_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    unit VARCHAR(50) NOT NULL, -- g, ml, pièce, etc.
    stock_quantity INT NOT NULL DEFAULT 0 -- Quantité disponible
);

-- Table de liaison recettes-ingrédients
CREATE TABLE recipe_ingredients (
    recipe_id INT REFERENCES recipes(recipe_id) ON DELETE CASCADE,
    ingredient_id INT REFERENCES ingredients(ingredient_id) ON DELETE CASCADE,
    quantity_needed INT NOT NULL,
    PRIMARY KEY (recipe_id, ingredient_id)
);

-- Table des ustensiles
CREATE TABLE ustensils (
    ustensil_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    status VARCHAR(50) DEFAULT 'Disponible' -- Disponible, En utilisation, Hors service
);

-- Table des équipements
CREATE TABLE equipment (
    equipment_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    max_capacity INT DEFAULT NULL, -- Null pour les équipements sans capacité définie
    current_usage INT DEFAULT 0, -- Capacité actuellement utilisée
    status VARCHAR(50) DEFAULT 'Disponible'
);

-- Table de liaison recettes-ustensiles
CREATE TABLE recipe_ustensils (
    recipe_id INT REFERENCES recipes(recipe_id) ON DELETE CASCADE,
    ustensil_id INT REFERENCES ustensils(ustensil_id) ON DELETE CASCADE,
    PRIMARY KEY (recipe_id, ustensil_id)
);

-- Table de liaison recettes-équipements
CREATE TABLE recipe_equipment (
    recipe_id INT REFERENCES recipes(recipe_id) ON DELETE CASCADE,
    equipment_id INT REFERENCES equipment(equipment_id) ON DELETE CASCADE,
    PRIMARY KEY (recipe_id, equipment_id)
);

-- Table des processus (étapes des recettes)
CREATE TABLE process_steps (
    step_id SERIAL PRIMARY KEY,
    recipe_id INT REFERENCES recipes(recipe_id) ON DELETE CASCADE,
    description TEXT NOT NULL,
    duration INT NOT NULL, -- Durée en minutes
    step_order INT NOT NULL -- Ordre des étapes
);

-- Table des tâches
CREATE TABLE tasks (
    task_id SERIAL PRIMARY KEY,
    recipe_id INT REFERENCES recipes(recipe_id) ON DELETE CASCADE,
    description TEXT,
    estimated_time INT NOT NULL,
    status VARCHAR(50) DEFAULT 'En attente' -- En attente, En cours, Terminé
);

-- Table de gestion des matériaux
CREATE TABLE material_stock (
    material_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    category VARCHAR(100), -- Exemple : Vaisselle, Textiles, Autres
    quantity INT NOT NULL DEFAULT 0
);

-- Table de liaison tâches-FIFO
CREATE TABLE task_queue (
    task_id INT REFERENCES tasks(task_id) ON DELETE CASCADE,
    queue_position SERIAL PRIMARY KEY -- Ordre FIFO basé sur SERIAL
);







-- 2. Insertion des Données



-- 2.1 Recettes
-- Insertion des recettes (Entrées)
INSERT INTO recipes (name, preparation_time, cooking_time, description) VALUES
('Feuilleté au crabe', 10, 20, 'Mélanger les ingrédients, garnir la pâte et cuire.'),
('Œufs cocotte', 10, 5, 'Cuire blancs au bain-marie, ajouter jaunes.'),
('Salade César', 15, 0, 'Mélanger laitue avec garnitures.'),
('Soupe froide de concombre', 10, 0, 'Mixer concombre et yaourt, ajouter ail, menthe, citron.'),
('Bruschetta', 10, 5, 'Griller pain, ajouter mélange tomate-ail-huile-basilic.'),
('Tartare de saumon', 15, 0, 'Couper saumon et avocat en dés, assaisonner avec citron.'),
('Velouté de champignons', 10, 15, 'Faire revenir oignon et champignons, ajouter crème, mixer.'),
('Carpaccio de betterave', 10, 0, 'Couper betterave en tranches, garnir chèvre, noix, roquette.'),
('Mini quiches au fromage', 15, 20, 'Garnir pâte, mélanger œufs et fromage, cuire.'),
('Gaspacho', 15, 0, 'Mixer tous les ingrédients, servir froid.');

-- Insertion des recettes (Plats)
INSERT INTO recipes (name, preparation_time, cooking_time, description) VALUES
('Bouillinade de poissons', 10, 20, 'Superposer ingrédients dans cocotte, cuire.'),
('Boles de picoulats', 60, 0, 'Former boules, mijoter avec légumes.'),
('Blanquette de veau', 10, 120, 'Faire revenir viande, mijoter avec légumes.'),
('Poulet rôti au thym', 15, 60, 'Badigeonner poulet, rôtir avec thym et ail.'),
('Lasagnes végétariennes', 20, 40, 'Superposer couches légumes, béchamel, pâte, cuire.'),
('Gratin dauphinois', 15, 45, 'Disposer pommes de terre en couches, cuire avec crème.'),
('Ratatouille', 20, 30, 'Faire revenir légumes, mijoter.'),
('Bœuf bourguignon', 20, 120, 'Faire revenir viande, mijoter avec vin et légumes.'),
('Curry de légumes', 15, 30, 'Cuire légumes avec lait de coco et épices.'),
('Tagliatelles au saumon', 15, 10, 'Cuire pâtes, mélanger avec saumon et crème.');

-- Insertion des recettes (Desserts)
INSERT INTO recipes (name, preparation_time, cooking_time, description) VALUES
('Mousse au chocolat', 15, 0, 'Faire fondre chocolat, incorporer œufs battus.'),
('Tarte aux pommes', 20, 30, 'Garnir pâte, ajouter pommes, cuire.'),
('Crème brûlée', 15, 30, 'Cuire crème au bain-marie, caraméliser avec sucre.'),
('Tiramisu', 20, 0, 'Monter mascarpone, alterner avec biscuits imbibés de café.'),
('Fondant au chocolat', 15, 10, 'Mélanger ingrédients, cuire brièvement.'),
('Clafoutis aux cerises', 15, 40, 'Verser mélange sur cerises, cuire.'),
('Panna cotta', 10, 0, 'Chauffer crème, ajouter gélatine, réfrigérer.'),
('Millefeuille', 30, 0, 'Cuire pâte, alterner couches avec crème.'),
('Cheesecake', 20, 60, 'Préparer base biscuitée, garnir fromage, cuire.'),
('Tarte au citron meringuée', 30, 40, 'Garnir pâte de crème citron, ajouter meringue, cuire.');





-- 2.2 Ingrédients
-- Insertion des ingrédients
INSERT INTO ingredients (name, unit, stock_quantity) VALUES
('Pâte feuilletée', 'g', 1000),
('Chair de crabe', 'g', 800),
('Œufs', 'pièce', 500),
('Gruyère râpé', 'g', 200),
('Crème fraîche', 'ml', 500),
('Laitue romaine', 'pièce', 50),
('Croûtons', 'pièce', 200),
('Poulet grillé', 'g', 500),
('Parmesan', 'g', 300),
('Concombre', 'pièce', 100),
('Yaourt', 'pièce', 50),
('Ail', 'g', 500),
('Menthe', 'g', 100),
('Citron', 'pièce', 50),
('Pain', 'pièce', 50),
('Tomates', 'pièce', 200),
('Saumon', 'g', 800),
('Champignons', 'g', 800),
('Oignon', 'g', 500),
('Betterave', 'pièce', 50),
('Chèvre frais', 'g', 300),
('Noix', 'g', 300),
('Roquette', 'g', 200),
('Pommes de terre', 'pièce', 300),
('Crème', 'ml', 1000),
('Vin rouge', 'ml', 500),
('Carottes', 'pièce', 100),
('Légumes variés', 'g', 2000),
('Saumon fumé', 'g', 300),
('Chocolat noir', 'g', 1000),
('Mascarpone', 'g', 500),
('Biscuits', 'pièce', 100),
('Cerises', 'pièce', 100),
('Fromage frais', 'g', 800),
('Sucre', 'g', 500),
('Beurre', 'g', 500);






-- 2.3 Recettes-Ingrédients
-- Insertion des ingrédients pour chaque recette
INSERT INTO recipe_ingredients (recipe_id, ingredient_id, quantity_needed) VALUES
-- Entrées
(1, 1, 300), -- Feuilleté au crabe : 300g de pâte feuilletée
(1, 2, 200), -- Feuilleté au crabe : 200g de chair de crabe
(1, 3, 2),   -- Feuilleté au crabe : 2 œufs
(1, 4, 50),  -- Feuilleté au crabe : 50ml de crème fraîche

(2, 3, 2),   -- Œufs cocotte : 2 œufs
(2, 4, 20),  -- Œufs cocotte : 20ml de crème fraîche
(2, 5, 30),  -- Œufs cocotte : 30g de gruyère râpé

(3, 6, 1),   -- Salade César : 1 laitue romaine
(3, 7, 20),  -- Salade César : 20 croûtons
(3, 8, 100), -- Salade César : 100g de poulet grillé
(3, 9, 20),  -- Salade César : 20g de parmesan

(4, 10, 1),  -- Soupe froide de concombre : 1 concombre
(4, 11, 1),  -- Soupe froide de concombre : 1 yaourt
(4, 12, 10), -- Soupe froide de concombre : 10g d'ail
(4, 13, 5),  -- Soupe froide de concombre : 5g de menthe
(4, 14, 1),  -- Soupe froide de concombre : 1 citron

(5, 15, 2),  -- Bruschetta : 2 pains
(5, 16, 3),  -- Bruschetta : 3 tomates
(5, 12, 5),  -- Bruschetta : 5g d'ail

(6, 17, 200), -- Tartare de saumon : 200g de saumon
(6, 18, 100), -- Tartare de saumon : 100g d’avocat
(6, 14, 1),   -- Tartare de saumon : 1 citron

(7, 19, 300), -- Velouté de champignons : 300g de champignons
(7, 20, 50),  -- Velouté de champignons : 50g d’oignons
(7, 4, 50),   -- Velouté de champignons : 50ml de crème fraîche

(8, 21, 200), -- Carpaccio de betterave : 200g de betteraves
(8, 22, 50),  -- Carpaccio de betterave : 50g de chèvre frais
(8, 23, 30),  -- Carpaccio de betterave : 30g de noix

(9, 1, 300),  -- Mini quiches au fromage : 300g de pâte brisée
(9, 3, 3),    -- Mini quiches au fromage : 3 œufs
(9, 5, 50),   -- Mini quiches au fromage : 50g de gruyère râpé
(9, 4, 50),   -- Mini quiches au fromage : 50ml de crème fraîche

(10, 16, 5),  -- Gaspacho : 5 tomates
(10, 10, 1),  -- Gaspacho : 1 concombre
(10, 24, 1),  -- Gaspacho : 1 poivron
(10, 12, 10), -- Gaspacho : 10g d’ail

-- Plats
(11, 25, 500), -- Bouillinade de poissons : 500g de poissons variés
(11, 16, 2),   -- Bouillinade de poissons : 2 tomates
(11, 12, 10),  -- Bouillinade de poissons : 10g d’ail

(12, 26, 400), -- Boles de picoulats : 400g de chair à saucisse
(12, 27, 200), -- Boles de picoulats : 200g de bœuf haché

(13, 28, 500), -- Blanquette de veau : 500g de viande de veau
(13, 29, 200), -- Blanquette de veau : 200g de légumes variés
(13, 30, 1),   -- Blanquette de veau : 1 cube de bouillon

(14, 31, 1),   -- Poulet rôti au thym : 1 poulet entier
(14, 32, 5),   -- Poulet rôti au thym : 5g de thym

(15, 29, 300), -- Lasagnes végétariennes : 300g de légumes variés
(15, 33, 100), -- Lasagnes végétariennes : 100ml de béchamel

(16, 34, 5),   -- Gratin dauphinois : 5 pommes de terre
(16, 4, 50),   -- Gratin dauphinois : 50ml de crème

(17, 29, 300), -- Ratatouille : 300g de légumes variés
(17, 12, 10),  -- Ratatouille : 10g d’ail

(18, 35, 500), -- Bœuf bourguignon : 500g de viande de bœuf
(18, 30, 200), -- Bœuf bourguignon : 200ml de vin rouge
(18, 29, 100), -- Bœuf bourguignon : 100g de légumes variés

(19, 29, 300), -- Curry de légumes : 300g de légumes variés
(19, 36, 100), -- Curry de légumes : 100ml de lait de coco
(19, 37, 10),  -- Curry de légumes : 10g d’épices

(20, 38, 300), -- Tagliatelles au saumon : 300g de tagliatelles
(20, 4, 50),   -- Tagliatelles au saumon : 50ml de crème
(20, 17, 200), -- Tagliatelles au saumon : 200g de saumon fumé

-- Desserts
(21, 39, 200), -- Mousse au chocolat : 200g de chocolat noir
(21, 3, 2),    -- Mousse au chocolat : 2 œufs

(22, 1, 300),  -- Tarte aux pommes : 300g de pâte brisée
(22, 40, 2),   -- Tarte aux pommes : 2 pommes

(23, 41, 300), -- Crème brûlée : 300ml de crème
(23, 42, 3),   -- Crème brûlée : 3 jaunes d’œufs
(23, 43, 50),  -- Crème brûlée : 50g de sucre

(24, 44, 250), -- Tiramisu : 250g de mascarpone
(24, 45, 10),  -- Tiramisu : 10 biscuits
(24, 46, 100), -- Tiramisu : 100ml de café

(25, 39, 200), -- Fondant au chocolat : 200g de chocolat noir
(25, 43, 50),  -- Fondant au chocolat : 50g de sucre

(26, 47, 200), -- Clafoutis aux cerises : 200g de cerises
(26, 3, 2),    -- Clafoutis aux cerises : 2 œufs
(26, 4, 50),   -- Clafoutis aux cerises : 50ml de lait

(27, 41, 200), -- Panna cotta : 200ml de crème
(27, 48, 5),   -- Panna cotta : 5g de gélatine

(28, 1, 300),  -- Millefeuille : 300g de pâte feuilletée
(28, 49, 200), -- Millefeuille : 200g de crème pâtissière

(29, 44, 200), -- Cheesecake : 200g de fromage frais
(29, 45, 10),  -- Cheesecake : 10 biscuits

(30, 50, 2),   -- Tarte au citron meringuée : 2 citrons
(30, 1, 300);  -- Tarte au citron meringuée : 300g de pâte brisée






-- 2.4 Ustensiles
-- Insertion des ustensiles
INSERT INTO ustensils (name, status) VALUES
('Four', 'Disponible'),
('Bain-marie', 'Disponible'),
('Casserole', 'Disponible'),
('Mixeur', 'Disponible'),
('Mandoline', 'Disponible'),
('Moule à quiches', 'Disponible'),
('Rouleau à pâtisserie', 'Disponible'),
('Grille-pain', 'Disponible'),
('Couteau de cuisine', 'Disponible'),
('Bol à salade', 'Disponible');






-- 2.5 Recettes-Ustensiles
-- Insertion des ustensiles pour chaque recette
INSERT INTO recipe_ustensils (recipe_id, ustensil_id) VALUES
-- Entrées
(1, 1), -- Feuilleté au crabe : Four
(1, 9), -- Feuilleté au crabe : Bol
(1, 10), -- Feuilleté au crabe : Couteau
(2, 2), -- Œufs cocotte : Bain-marie
(2, 10), -- Œufs cocotte : Couteau
(3, 10), -- Salade César : Couteau
(3, 9), -- Salade César : Bol
(4, 4), -- Soupe froide de concombre : Mixeur
(4, 10), -- Soupe froide de concombre : Couteau
(5, 8), -- Bruschetta : Grille-pain
(5, 10), -- Bruschetta : Couteau
(6, 10), -- Tartare de saumon : Couteau
(6, 9), -- Tartare de saumon : Bol
(7, 3), -- Velouté de champignons : Casserole
(7, 4), -- Velouté de champignons : Mixeur
(7, 10), -- Velouté de champignons : Couteau
(8, 10), -- Carpaccio de betterave : Mandoline
(8, 9), -- Carpaccio de betterave : Bol
(9, 7), -- Mini quiches au fromage : Moule à quiches
(9, 1), -- Mini quiches au fromage : Four
(10, 4), -- Gaspacho : Mixeur
-- Plats
(11, 5), -- Bouillinade de poissons : Cocotte
(11, 10), -- Bouillinade de poissons : Couteau
(12, 5), -- Boles de picoulats : Cocotte
(12, 9), -- Boles de picoulats : Bol
(13, 5), -- Blanquette de veau : Cocotte
(13, 10), -- Blanquette de veau : Couteau
(14, 1), -- Poulet rôti au thym : Four
(14, 10), -- Poulet rôti au thym : Couteau
(15, 5), -- Lasagnes végétariennes : Cocotte
(15, 10), -- Lasagnes végétariennes : Couteau
(16, 6), -- Gratin dauphinois : Plat à gratin
(16, 10), -- Gratin dauphinois : Couteau
(17, 5), -- Ratatouille : Cocotte
(17, 10), -- Ratatouille : Couteau
(18, 5), -- Bœuf bourguignon : Cocotte
(18, 10), -- Bœuf bourguignon : Couteau
(19, 5), -- Curry de légumes : Cocotte
(19, 10), -- Curry de légumes : Couteau
(20, 3), -- Tagliatelles au saumon : Casserole
-- Desserts
(21, 4), -- Mousse au chocolat : Bol
(21, 6), -- Mousse au chocolat : Bain-marie
(22, 1), -- Tarte aux pommes : Four
(22, 7), -- Tarte aux pommes : Rouleau à pâtisserie
(23, 2), -- Crème brûlée : Bain-marie
(23, 9), -- Crème brûlée : Ramequins
(24, 9), -- Tiramisu : Bol
(25, 1), -- Fondant au chocolat : Four
(25, 9), -- Fondant au chocolat : Bol
(26, 1), -- Clafoutis aux cerises : Four
(26, 9), -- Clafoutis aux cerises : Bol
(27, 9), -- Panna cotta : Bol
(28, 1), -- Millefeuille : Rouleau à pâtisserie
(29, 9), -- Cheesecake : Bol
(29, 1), -- Cheesecake : Four
(30, 1), -- Tarte au citron meringuée : Four
(30, 9); -- Tarte au citron meringuée : Bol




-- 2.6 Équipements
-- Insertion des équipements
INSERT INTO equipment (name, max_capacity, status) VALUES
('Réfrigérateur', 10, 'Disponible'),
('Congélateur', 20, 'Disponible'),
('Machine à laver', NULL, 'Disponible'),
('Évier', NULL, 'Disponible'),
('Lave-vaisselle', 24, 'Disponible');





-- 2.7 Recettes-Équipements
-- Insertion des équipements pour chaque recette
INSERT INTO recipe_equipment (recipe_id, equipment_id) VALUES
-- Entrées
(1, 1), -- Feuilleté au crabe : Four
(2, 1), -- Œufs cocotte : Réfrigérateur
(3, 1), -- Salade César : Réfrigérateur
(4, 1), -- Soupe froide de concombre : Réfrigérateur
(5, 1), -- Bruschetta : Four
-- Plats
(11, 1), -- Bouillinade de poissons : Réfrigérateur
(12, 1), -- Boles de picoulats : Réfrigérateur
(13, 1), -- Blanquette de veau : Réfrigérateur
(14, 1), -- Poulet rôti au thym : Four
-- Desserts
(21, 1), -- Mousse au chocolat : Réfrigérateur
(22, 1), -- Tarte aux pommes : Réfrigérateur
(23, 1), -- Crème brûlée : Réfrigérateur
(24, 1), -- Tiramisu : Réfrigérateur;





-- 2.8 Étapes des Recettes
-- Étapes pour les recettes
INSERT INTO process_steps (recipe_id, description, duration, step_order) VALUES
-- Entrées
(1, 'Mélanger les ingrédients (crabe, œufs, crème).', 5, 1),
(1, 'Garnir la pâte feuilletée avec le mélange.', 5, 2),
(1, 'Cuire au four à 200°C.', 20, 3),

(2, 'Séparer les blancs des jaunes.', 3, 1),
(2, 'Cuire les blancs au bain-marie.', 5, 2),
(2, 'Ajouter les jaunes au moment de servir.', 2, 3),

(3, 'Laver la laitue romaine.', 5, 1),
(3, 'Couper le poulet en morceaux.', 5, 2),
(3, 'Assembler avec croûtons, parmesan, et sauce César.', 5, 3),

(4, 'Éplucher le concombre.', 3, 1),
(4, 'Mixer concombre, yaourt, ail, et menthe.', 5, 2),
(4, 'Ajouter le citron et assaisonner.', 2, 3),

(5, 'Couper le pain en tranches.', 3, 1),
(5, 'Faire griller le pain.', 5, 2),
(5, 'Garnir avec le mélange tomate-ail-huile.', 5, 3),

(6, 'Découper le saumon en petits dés.', 5, 1),
(6, 'Couper l’avocat en dés.', 5, 2),
(6, 'Mélanger le tout avec le jus de citron.', 3, 3),

(7, 'Faire revenir les oignons dans une casserole.', 5, 1),
(7, 'Ajouter les champignons et faire mijoter.', 10, 2),
(7, 'Mixer avec de la crème.', 5, 3),

(8, 'Éplucher et couper la betterave en tranches fines.', 5, 1),
(8, 'Disposer sur une assiette.', 3, 2),
(8, 'Garnir avec chèvre, noix, et roquette.', 3, 3),

(9, 'Mélanger œufs, fromage râpé, et crème.', 5, 1),
(9, 'Garnir la pâte brisée avec le mélange.', 5, 2),
(9, 'Cuire au four.', 20, 3),

(10, 'Laver et couper les légumes.', 5, 1),
(10, 'Mixer tous les ingrédients.', 10, 2),
(10, 'Servir froid.', 2, 3),

-- Plats
(11, 'Nettoyer et couper les poissons.', 10, 1),
(11, 'Disposer les poissons dans la cocotte.', 5, 2),
(11, 'Ajouter les légumes et cuire.', 20, 3),

(12, 'Préparer les boulettes avec la viande hachée.', 15, 1),
(12, 'Faire revenir les boulettes.', 15, 2),
(12, 'Ajouter la sauce et mijoter.', 30, 3),

(13, 'Faire revenir la viande dans la cocotte.', 10, 1),
(13, 'Ajouter les légumes et le bouillon.', 10, 2),
(13, 'Mijoter à feu doux.', 120, 3),

(14, 'Nettoyer et assaisonner le poulet.', 10, 1),
(14, 'Badigeonner avec du beurre et du thym.', 5, 2),
(14, 'Rôtir au four.', 60, 3),

(15, 'Préparer les légumes pour la garniture.', 10, 1),
(15, 'Superposer les couches de légumes, béchamel, et pâte.', 10, 2),
(15, 'Cuire au four.', 40, 3),

(16, 'Éplucher et couper les pommes de terre.', 10, 1),
(16, 'Disposer en couches dans le plat.', 5, 2),
(16, 'Cuire au four.', 45, 3),

(17, 'Couper les légumes en morceaux.', 10, 1),
(17, 'Faire revenir les légumes dans une cocotte.', 10, 2),
(17, 'Mijoter à feu doux.', 30, 3),

(18, 'Faire revenir la viande dans une cocotte.', 10, 1),
(18, 'Ajouter les légumes et le vin rouge.', 10, 2),
(18, 'Mijoter à feu doux.', 120, 3),

(19, 'Couper les légumes en morceaux.', 10, 1),
(19, 'Faire revenir avec les épices.', 10, 2),
(19, 'Ajouter le lait de coco et mijoter.', 10, 3),

(20, 'Cuire les pâtes dans une casserole d’eau bouillante.', 10, 1),
(20, 'Égoutter les pâtes.', 2, 2),
(20, 'Mélanger avec le saumon fumé et la crème.', 5, 3),

-- Desserts
(21, 'Faire fondre le chocolat au bain-marie.', 10, 1),
(21, 'Battre les œufs en neige.', 5, 2),
(21, 'Incorporer les œufs au chocolat fondu.', 5, 3),

(22, 'Préparer la pâte brisée.', 10, 1),
(22, 'Couper les pommes et les disposer sur la pâte.', 10, 2),
(22, 'Cuire au four.', 30, 3),

(23, 'Mélanger la crème, les jaunes d’œufs, et le sucre.', 10, 1),
(23, 'Cuire le mélange au bain-marie.', 15, 2),
(23, 'Caraméliser avec du sucre au chalumeau.', 5, 3),

(24, 'Monter la crème mascarpone.', 10, 1),
(24, 'Imbiber les biscuits de café.', 5, 2),
(24, 'Assembler en couches mascarpone et biscuits.', 5, 3),

(25, 'Faire fondre le chocolat et le beurre.', 10, 1),
(25, 'Ajouter le sucre, les œufs, et la farine.', 5, 2),
(25, 'Cuire au four.', 10, 3),

(26, 'Préparer le mélange avec les cerises et la pâte.', 10, 1),
(26, 'Verser dans un plat à gratin.', 5, 2),
(26, 'Cuire au four.', 40, 3),

(27, 'Chauffer la crème avec le sucre et la vanille.', 5, 1),
(27, 'Ajouter la gélatine.', 5, 2),
(27, 'Réfrigérer jusqu’à ce que la panna cotta prenne.', 120, 3),

(28, 'Cuire la pâte feuilletée.', 15, 1),
(28, 'Assembler avec la crème pâtissière.', 10, 2),
(28, 'Saupoudrer de sucre glace.', 5, 3),

(29, 'Préparer la base biscuitée.', 10, 1),
(29, 'Mélanger la garniture au fromage.', 10, 2),
(29, 'Cuire au four.', 60, 3),

(30, 'Préparer la crème citron.', 10, 1),
(30, 'Garnir la pâte avec la crème.', 10, 2),
(30, 'Ajouter la meringue et cuire au four.', 40, 3);





-- 2.9 Tâches
INSERT INTO tasks (recipe_id, description, estimated_time, status) VALUES
(1, 'Préparer Feuilleté au crabe', 30, 'En attente'),
(2, 'Préparer Œufs cocotte', 15, 'En attente');






-- 2.10 Matériaux
INSERT INTO material_stock (name, category, quantity) VALUES
('Assiettes petites', 'Vaisselle', 150),
('Fourchettes', 'Couverts', 150),
('Verres à eau', 'Vaisselle', 150),
('Serviettes en tissu', 'Textiles', 150),
('Bouteilles d’eau', 'Autres', 40);


