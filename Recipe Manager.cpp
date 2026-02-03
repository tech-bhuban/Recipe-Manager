

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>

struct Ingredient {
    std::string name;
    double quantity;
    std::string unit;
    
    void display() const {
        std::cout << "- " << quantity << " " << unit << " " << name << "\n";
    }
};

struct Recipe {
    std::string name;
    std::string category;
    int prepTime;  // in minutes
    int cookTime;  // in minutes
    int servings;
    std::vector<Ingredient> ingredients;
    std::vector<std::string> instructions;
    double rating; // 1-5
    
    void display() const {
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << name << " (" << category << ")\n";
        std::cout << std::string(50, '-') << "\n";
        std::cout << "Prep: " << prepTime << " min | Cook: " << cookTime 
                 << " min | Servings: " << servings << " | Rating: " 
                 << std::fixed << std::setprecision(1) << rating << "/5\n\n";
        
        std::cout << "INGREDIENTS:\n";
        for (const auto& ing : ingredients) {
            ing.display();
        }
        
        std::cout << "\nINSTRUCTIONS:\n";
        for (size_t i = 0; i < instructions.size(); i++) {
            std::cout << i + 1 << ". " << instructions[i] << "\n";
        }
        std::cout << std::string(50, '=') << "\n";
    }
    
    int getTotalTime() const {
        return prepTime + cookTime;
    }
    
    double getCostEstimate(double avgCostPerServing = 2.5) const {
        return servings * avgCostPerServing;
    }
};

class RecipeManager {
private:
    std::vector<Recipe> recipes;
    
public:
    void addRecipe(const Recipe& recipe) {
        recipes.push_back(recipe);
    }
    
    void displayAllRecipes() {
        std::cout << "\n=== RECIPE COLLECTION ===\n";
        std::cout << "Total Recipes: " << recipes.size() << "\n\n";
        
        for (size_t i = 0; i < recipes.size(); i++) {
            std::cout << i + 1 << ". " << recipes[i].name 
                     << " (" << recipes[i].category << ") - "
                     << recipes[i].getTotalTime() << " min - ⭐" 
                     << std::fixed << std::setprecision(1) << recipes[i].rating << "\n";
        }
    }
    
    void searchByCategory(const std::string& category) {
        std::cout << "\n=== " << category << " RECIPES ===\n";
        bool found = false;
        
        for (const auto& recipe : recipes) {
            if (recipe.category == category) {
                recipe.display();
                found = true;
            }
        }
        
        if (!found) {
            std::cout << "No recipes found in category: " << category << "\n";
        }
    }
    
    void searchByIngredient(const std::string& ingredient) {
        std::cout << "\n=== RECIPES WITH " << ingredient << " ===\n";
        bool found = false;
        
        for (const auto& recipe : recipes) {
            for (const auto& ing : recipe.ingredients) {
                if (ing.name.find(ingredient) != std::string::npos) {
                    std::cout << "- " << recipe.name << " (" << recipe.category << ")\n";
                    found = true;
                    break;
                }
            }
        }
        
        if (!found) {
            std::cout << "No recipes found with ingredient: " << ingredient << "\n";
        }
    }
    
    void quickRecipes(int maxTime) {
        std::cout << "\n=== QUICK RECIPES (<" << maxTime << " min) ===\n";
        bool found = false;
        
        for (const auto& recipe : recipes) {
            if (recipe.getTotalTime() <= maxTime) {
                std::cout << "- " << recipe.name << ": " << recipe.getTotalTime() 
                         << " min, Serves: " << recipe.servings << "\n";
                found = true;
            }
        }
        
        if (!found) {
            std::cout << "No recipes found under " << maxTime << " minutes\n";
        }
    }
    
    void displayStatistics() {
        if (recipes.empty()) {
            std::cout << "No recipes available for statistics.\n";
            return;
        }
        
        std::map<std::string, int> categoryCount;
        int totalTime = 0;
        double totalRating = 0;
        Recipe* quickest = &recipes[0];
        Recipe* highestRated = &recipes[0];
        
        for (const auto& recipe : recipes) {
            categoryCount[recipe.category]++;
            totalTime += recipe.getTotalTime();
            totalRating += recipe.rating;
            
            if (recipe.getTotalTime() < quickest->getTotalTime()) {
                quickest = const_cast<Recipe*>(&recipe);
            }
            if (recipe.rating > highestRated->rating) {
                highestRated = const_cast<Recipe*>(&recipe);
            }
        }
        
        std::cout << "\n=== RECIPE STATISTICS ===\n";
        std::cout << "Total Recipes: " << recipes.size() << "\n";
        std::cout << "Average Prep Time: " << totalTime / recipes.size() << " min\n";
        std::cout << "Average Rating: " << std::fixed << std::setprecision(1) 
                 << totalRating / recipes.size() << "/5\n";
        
        std::cout << "\nBy Category:\n";
        for (const auto& pair : categoryCount) {
            std::cout << "- " << pair.first << ": " << pair.second << " recipes\n";
        }
        
        std::cout << "\nQuickest Recipe: " << quickest->name 
                 << " (" << quickest->getTotalTime() << " min)\n";
        std::cout << "Highest Rated: " << highestRated->name 
                 << " (⭐" << std::fixed << std::setprecision(1) 
                 << highestRated->rating << ")\n";
    }
};

// Sample recipes
Recipe createSpaghetti() {
    Recipe spaghetti;
    spaghetti.name = "Classic Spaghetti Bolognese";
    spaghetti.category = "Italian";
    spaghetti.prepTime = 15;
    spaghetti.cookTime = 45;
    spaghetti.servings = 4;
    spaghetti.rating = 4.5;
    
    spaghetti.ingredients = {
        {"spaghetti", 400, "g"},
        {"ground beef", 500, "g"},
        {"onion", 1, "large"},
        {"garlic cloves", 3, ""},
        {"canned tomatoes", 400, "g"},
        {"tomato paste", 2, "tbsp"},
        {"olive oil", 2, "tbsp"},
        {"salt", 1, "tsp"},
        {"black pepper", 0.5, "tsp"}
    };
    
    spaghetti.instructions = {
        "Boil water with salt and cook spaghetti according to package instructions.",
        "Heat olive oil in a large pan over medium heat.",
        "Add chopped onion and garlic, cook until softened.",
        "Add ground beef and cook until browned.",
        "Stir in tomatoes and tomato paste, simmer for 30 minutes.",
        "Season with salt and pepper.",
        "Serve spaghetti with sauce on top."
    };
    
    return spaghetti;
}

Recipe createChocolateChipCookies() {
    Recipe cookies;
    cookies.name = "Chocolate Chip Cookies";
    cookies.category = "Dessert";
    cookies.prepTime = 20;
    cookies.cookTime = 12;
    cookies.servings = 24;
    cookies.rating = 4.8;
    
    cookies.ingredients = {
        {"all-purpose flour", 2.25, "cups"},
        {"baking soda", 1, "tsp"},
        {"salt", 1, "tsp"},
        {"butter", 1, "cup"},
        {"granulated sugar", 0.75, "cup"},
        {"brown sugar", 0.75, "cup"},
        {"vanilla extract", 1, "tsp"},
        {"eggs", 2, "large"},
        {"chocolate chips", 2, "cups"}
    };
    
    cookies.instructions = {
        "Preheat oven to 375°F (190°C).",
        "Mix flour, baking soda, and salt in a bowl.",
        "In another bowl, cream butter and sugars until fluffy.",
        "Beat in eggs one at a time, then add vanilla.",
        "Gradually blend in the flour mixture.",
        "Stir in chocolate chips.",
        "Drop by rounded tablespoons onto ungreased baking sheets.",
        "Bake for 9-11 minutes until golden brown.",
        "Cool on baking sheets for 2 minutes, then transfer to wire racks."
    };
    
    return cookies;
}

int main() {
    RecipeManager manager;
    
    // Add sample recipes
    manager.addRecipe(createSpaghetti());
    manager.addRecipe(createChocolateChipCookies());
    
    int choice;
    do {
        std::cout << "\n=== RECIPE MANAGER ===\n";
        std::cout << "1. View All Recipes\n";
        std::cout << "2. Search by Category\n";
        std::cout << "3. Search by Ingredient\n";
        std::cout << "4. Find Quick Recipes\n";
        std::cout << "5. Show Statistics\n";
        std::cout << "6. Add New Recipe\n";
        std::cout << "7. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 1) {
            manager.displayAllRecipes();
        } else if (choice == 2) {
            std::string category;
            std::cout << "Enter category: ";
            std::getline(std::cin, category);
            manager.searchByCategory(category);
        } else if (choice == 3) {
            std::string ingredient;
            std::cout << "Enter ingredient: ";
            std::getline(std::cin, ingredient);
            manager.searchByIngredient(ingredient);
        } else if (choice == 4) {
            int maxTime;
            std::cout << "Maximum preparation time (minutes): ";
            std::cin >> maxTime;
            manager.quickRecipes(maxTime);
        } else if (choice == 5) {
            manager.displayStatistics();
        } else if (choice == 6) {
            std::cout << "Recipe creation feature coming soon!\n";
        }
    } while (choice != 7);
    
    return 0;
}


// # 🍳 Recipe Manager

// A comprehensive digital recipe book with search, categorization, and meal planning features.

// ## 📚 Features
// - **Recipe Database**: Store and organize recipes
// - **Smart Search**: Search by category, ingredient, or preparation time
// - **Nutritional Info**: Track ingredients and servings
// - **Meal Planning**: Find recipes based on available time
// - **Statistics**: Analytics on recipe collection
// - **Detailed View**: Complete recipe display with ingredients and instructions

// ## 🚀 Quick Start
// ```bash
// # Compile
// g++ -o recipe_manager recipe_manager.cpp

// # Run
// ./recipe_manager