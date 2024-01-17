import openai
import os
import math
import sys

# Initialize OpenAI API
openai.api_type = "azure"
openai.api_base = "https://hkust.azure-api.net"
openai.api_version= "2023-05-15"
openai.api_key = "c250a74f8ce34702bfbaf6a9b023e58e"

class Assistant:
    def __init__(self):
        self.engine = "gpt-35-turbo"
        self.max_int = 0
        self.last = 0
        self.place = ''
        self.check = False
        self.system_role = "you are a helpful secretary."
        self.context = ""
        self.dict = {"myhouse": "1", "houseb": "2", "crafting": "0", "npchousea": "3", "garden": "0", "village": "0", "dungeon": "0", "cafeteria":"0"}
        self.status = {"I":"myhouse", "playerB": "houseb", "npc1": "npchousea"}
        self.name = {"0":"no one", "1": "I", "2": "Olive", "3":"NPC1"}
        self.textDetected = ""
        self.map = [
            ["", "", "", ""],
            ["****************", "GAME", "MAP", "*****************"],
            ["", "", "", ""],
            [" MyHouse", "    HouseB", "   Crafting", "  NPCHouseA"],
            ["+--------+", "+--------+", "+--------+", "+--------+"],
            ["|        |", "|        |", "|        |", "|        |"],
            ["|    1   |", "|    2   |", "|    0   |", "|    3   |"],
            ["|        |", "|        |", "|        |", "|        |"],
            ["+--------+", "+--------+", "+--------+", "+--------+"],
            ["", "", "", ""],
            ["  garden", "   Village", "   Dungeon", "  Cafeteria"],
            ["+--------+", "+--------+", "+--------+", "+--------+"],
            ["|        |", "|        |", "|        |", "|        |"],
            ["|    0   |", "|    0   |", "|    0   |", "|    0   |"],
            ["|        |", "|        |", "|        |", "|        |"],
            ["+--------+", "+--------+", "+--------+", "+--------+"],
            ["", "", "", ""]
        ]

        
    def mapCreation(self):
        d = 0
        for b, (i, j) in zip(range(4), self.dict.items()):
            self.map[6][d] = f"|    {j}   |"
            d+=1
        
        d = 0
        for b, (i, j) in zip(range(8), self.dict.items()):
            if b > 3:
                self.map[13][d] = f"|    {j}   |"
                d+=1
                    
    def printMap(self):
        for row in self.map:
            print(" ".join(row))

    def get_user_input(self, prompt):
        user_prompt = input(prompt)
        while not prompt:
            print("Input cannot be empty.")
            user_prompt = input(prompt)
        return user_prompt

    def get_schedule(self, context):
        answer_prompt = f"With this specific context: '{context}' make a schedule from 9a.m to 9a.m the next day in 1 hour intervals: "
        return self.generate_answer(answer_prompt)

    def generate_answer(self, answer_prompt):
        try:
            response = openai.ChatCompletion.create(
                engine=self.engine,
                messages=[
                    {"role": "system", "content": self.system_role},
                    {"role": "user", "content": answer_prompt}
                ],
            )
            return response['choices'][0]['message']['content']
        
        except Exception as e:
            print(f"An error occurred: {e}")
            return None
     
    def weekly(self, context):
        theWeek = self.generate_answer(" '{context}'")
        print(theWeek)
    
    def put_txt(self, script, filename):
        with open(filename, 'w') as file:
            for line in script:
                file.write(' '.join(str(cell) for cell in line) + '\n')
    
    def interaction(self, temp, person):
        if temp == '0':
            return False
        elif temp == '1':
            if person == 'me':
                return False
            return 'me'
        elif temp == '2':
            if person == 'npc1':
                return False
            return 'Olive'
        elif temp == '3':
            if person == 'npc1':
                return False
            return 'npc1'
            
    
    def talk(self, person, place):
        newText = f"Make me an interaction with '{person}' in '{place}' and talk to me in a game setting'"
        newText = self.generate_answer(newText)
        print(newText)
        while True:
            response = input("what else do you want to ask? (write exit to exit interaction): \n")
            if response == "exit":
                return
            newText = f"make an interaction with '{person}' and ask him this '{response}' in '{place}', this is the context '{newText}' in a game setting"
            newText = self.generate_answer(newText)
            print(newText)
    
    def move(self):
        venue = input("Where do you want to go (write the name of the venue or 'quit' to exit): ")
        venue = venue.lower()

        while venue not in self.dict and venue.lower() != 'quit':
            venue = input("Invalid venue. Where do you want to go (write the name of the venue or 'quit' to exit): ")
            venue = venue.lower()
        
        if venue == 'quit':
            sys.exit()
        

        if venue != self.status["I"]:
            new_temp = self.dict[venue]
            
            if self.status["npc1"] != self.dict[self.status["I"]]:
                self.dict[self.status["I"]] = '0'
            else:
                self.dict[self.status["I"]] = self.last
                
            self.dict[venue] = "1"
            self.status["I"] = venue
            self.last = new_temp

            person = self.interaction(self.last, 'me')

            # interaction
            if person:
                self.printMap()
                print(f"{self.name[self.dict[venue]]} is in {venue} with {person}\n")
                self.talk(self.last, venue)
    
    def startPoint(self):
        see = False
        for i,j in self.dict.items():
            if j == '2':
                return True
        return False
    
    def endPoint(self):
        see = False
        k = 0
        for i,j in self.dict.items():
            if j == '1':                    
                k+=1
                if k == 2:
                    self.dict[i] = '0'
            
    def textDetection(self, context):
        self.check = False

        temp = '0'
        temp1 = '0'
        z = 0

        for i in context:
            if i == '' or i.isalpha():
                continue
            
            print('\n', i)
            words = i.split()

            for j in words:
                j = j.lower()
                if j in self.dict:
                    z+=1
                    if z == 1:
                        continue
                    if not self.status["npc1"] == j:
                        self.check = True
                        temp1 = self.dict[j]

                        if self.dict[j] != '1':
                            self.dict[j] = "3"
                        
                        if self.dict[self.status["npc1"]] != '1':
                            self.dict[self.status["npc1"]] = temp
                    
                        temp = temp1
                        self.status["npc1"] = j

                        person = self.interaction(temp, 'npc1')
                        # interaction
                        if person:
                            self.printMap()
                            if person == 'me' and self.dict[j] == '1':
                                person = 'npc1'
                            print(f"{self.name[self.dict[j]]} is in {j} with {person}\n")
                            self.talk(temp, j)
                            break

            if not self.startPoint() and self.dict['houseb'] == '0':
                self.dict['houseb'] = '2'
                
            self.endPoint()
            self.mapCreation()
            self.printMap()
            self.move()

        return self.check
    
    def run(self):
        prompt = input("1. Game Context\n2. Custom\n")
        
        while prompt != "1" and prompt != "2":
            print("Enter a valid option")
            prompt = input("")
        
        
        if prompt == "2":
            self.context = self.get_user_input("Write me a context for a day in a life of an npc: ")
            schedule = self.get_schedule(self.context)
            print(schedule)
            while True:
                user_prompt = self.get_user_input("What list of interaction/context do you want to add? (write 'refresh' if you want to refresh the context and exit to quit): ")
                
                if user_prompt.lower() == "refresh":
                    print("Context cleared.")
                    self.context = self.get_user_input("Write me another context: ")
                if user_prompt.lower() == 'quit':
                    sys.exit()
                else:
                    self.context += " " + user_prompt

                print(self.get_schedule(self.context))
       
        else:
            self.context = "In this game map, you are npc1 living in npchousea and can explore myhouse, HouseB, a crafting station, npchouseA, garden, a village, a dungeon, and a cafeteria, using these locations as keywords for actions. You are a game character"
            
            turn = False
            change = False
            
            while not change:
                start = 0
                end = 0
                while not turn:
                    schedule = self.get_schedule(self.context)
                    schedule1 = schedule
                    schedule = schedule.split("\n")
                    schedule = [item for item in schedule if item != '']
                    
                    for i in schedule:
                        if i.startswith('9'):
                            turn = True
                        if not turn:
                            start+=1
                    for i in schedule[::-1]:
                        if i != '' and i[0].isnumeric():
                            break
                        end+=1
                _end = len(schedule) - end
                change = self.textDetection(schedule[start:_end])     
                     
            print(schedule1)
            print("================= Thanks for playing =================")
            
if __name__ == "__main__":
    Assistant().run()