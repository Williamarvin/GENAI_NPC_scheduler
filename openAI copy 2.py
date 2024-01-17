import requests
import openai
import json
import os
import PyPDF2 as PyPDF
import html2text
import pandas as pd

# Initialize OpenAI API
openai.api_type = "azure"
openai.api_base = "https://hkust.azure-api.net"
openai.api_version= "2023-05-15"
openai.api_key = "c250a74f8ce34702bfbaf6a9b023e58e"

    
def extract_pdf(pdf_file):
    #path = os.path.join("pdf", pdf_file)
    os.chdir("pdf")
    with open(pdf_file, 'rb') as pdf:
        reader = PyPDF.PdfReader(pdf, strict=False)
        pdf_text = []
        
        for page in reader.pages:
            content = page.extract_text()
            pdf_text.append(content)
        os.chdir("..")
        return pdf_text
    

def extract_html(html):
    #path = os.path.join("pdf", pdf_file)
    os.chdir("pdf")
    
    with open(html, 'r') as file:
        html_content = file.read()
    converter = html2text.HTML2Text()
    converter.ignore_links = True  # Ignore hyperlinks
    text = converter.handle(html_content)
    os.chdir("..")
    os.chdir("..")
    return text

def extract_txt(txt):
    #path = os.path.join("pdf", pdf_file)
    os.chdir(txt)
    
    with open(txt, 'r') as file:
        data = file.read().replace('\n', '')
    os.chdir("..")
    os.chdir("..")
    return data

def extract_csv(csv):
    # Read the CSV file into a pandas DataFrame
    df = pd.read_csv(csv)

    # Select the second column and convert it to a text Series
    text_series = df.iloc[:, 1].astype(str)

    # Join the text Series into a single string
    text_string = ' '.join(text_series)
    os.chdir("..")
    os.chdir("..")
    return text_string

def main():
    # Get user input
    # print("a). Unity\nb). BiliBili \nc) Apple")
    # company = input("which company, input a, b, or c\n")
    file_path = "pdf"
    
    
    # while True:
    #     if company == "a":
    #         file_path = "pdf/unity"
    #         break
    #     elif company == "b":
    #         file_path = "pdf/bilibili"
    #         break
    #     elif company == "c":
    #         file_path = "pdf/apple"
    #         break
    #     else:
    #         company = input("which company, input a, b, or c")
    
    user_prompt = input("Enter your query about the company: ")
    #user_prompt = "Can you summarize and detail on the financial statements provided on the files provided?"

    text = ''
    text_string = ' '
    
    for filename in os.listdir(file_path):
        if filename.endswith('.pdf'):
            pdfContent = extract_pdf(filename)
            text_string += ' '.join(pdfContent)
            
        elif filename.endswith('.htm') or filename.endswith('.html'):
            htmlContent = extract_html(filename)
            text_string += ' '.join(htmlContent)

        elif filename.endswith('.txt'):
            txtContent = extract_txt(filename)
            text_string += ' '.join(txtContent)

        elif filename.endswith('.csv'):
            csvContent = extract_csv(filename)
            text_string += ' '.join(csvContent)
            #text_string = text_string.join
    
    max_tokens = 100
    
    while not user_prompt:
        print("Query cannot be empty")
        user_prompt = input("Enter your query about the PDF: ")

    content = text_string.replace('\n', ' ')
    content = text_string.replace(' ', '')
    print(content)

    answer_prompt = f"The user said: '{user_prompt}' with these information '{content}'."

    answer = openai.ChatCompletion.create(
        engine = "gpt-35-turbo",
        messages = [
            {"role": "system", "content": "you are a helpful assistant."},
            {"role": "user", "content": answer_prompt}
        ]
    )

    text = text.join(content)
    text = text.join(user_prompt)
    # Print the answer
    print("Answer", answer['choices'][0]['message']['content'])
    
    while True:
        user_prompt = input("what else do you want to ask?")
        print("write refresh if you want to restart the knowledge")
        if user_prompt == "refresh":
            print("cleared")
            text = ""
            user_prompt = input("what else do you want to ask?")

        answer_prompt = f"The user said: '{user_prompt}', if the user said something irrelevant completely ignore these '{text}'."

        answer = openai.ChatCompletion.create(
            engine = "gpt-35-turbo",
            messages = [
                {"role": "system", "content": "you are a helpful assistant."},
                {"role": "user", "content": answer_prompt}
        ]
    )
        
        print(answer['choices'][0]['message']['content'])
        text = text.join(user_prompt)
        text = text.join(answer)
        text = text_string.strip()

        
if __name__ == "__main__":
    main()