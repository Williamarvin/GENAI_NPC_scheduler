dict = {"dungeon": ("w","1"), "myhouse": "s", "npchouse1": "d", "npchouse2": "c", "cafeteria": "t", "village": "v", "crafting": "g", "houseb":"z"}

hello  = dict.get("dungeon", {})
print(dict.get("dungeon"))

print(hello[1])

def interaction(temp):
    if temp == '0':
        return False
    elif temp == '2':
        return 'Olive'
    elif temp == '3':
        return 'npc1'
    elif temp == '4':
        return 'npc2'
    
print(interaction("0"))