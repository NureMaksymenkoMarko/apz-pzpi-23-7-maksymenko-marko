# Приклад 1. Отримання списку листів через Gmail API

from googleapiclient.discovery import build

def list_messages(credentials):
    service = build("gmail", "v1", credentials=credentials)

    result = service.users().messages().list(
        userId="me",
        maxResults=10,
        q="in:inbox"
    ).execute()

    messages = result.get("messages", [])

    for message in messages:
        print("Message ID:", message["id"])


# Приклад 2. Отримання повної інформації про лист

def get_message(credentials, message_id):
    service = build("gmail", "v1", credentials=credentials)

    message = service.users().messages().get(
        userId="me",
        id=message_id,
        format="metadata"
    ).execute()

    print("Snippet:", message.get("snippet"))


# Приклад 3. Створення чернетки листа

import base64
from email.mime.text import MIMEText

def create_draft(credentials, to_email, subject, body_text):
    service = build("gmail", "v1", credentials=credentials)

    message = MIMEText(body_text)
    message["to"] = to_email
    message["subject"] = subject

    raw_message = base64.urlsafe_b64encode(
        message.as_bytes()
    ).decode("utf-8")

    draft_body = {
        "message": {
            "raw": raw_message
        }
    }

    draft = service.users().drafts().create(
        userId="me",
        body=draft_body
    ).execute()

    print("Draft ID:", draft["id"])


# Приклад 4. Додавання мітки до повідомлення

def add_label_to_message(credentials, message_id, label_id):
    service = build("gmail", "v1", credentials=credentials)

    service.users().messages().modify(
        userId="me",
        id=message_id,
        body={
            "addLabelIds": [label_id],
            "removeLabelIds": []
        }
    ).execute()

    print("Label added successfully")