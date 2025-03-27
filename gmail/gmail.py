#!/usr/bin/python3
# -*- coding: utf-8 -*-

import argparse
import configparser
import os
import sys

from base64 import urlsafe_b64encode
from email.mime.text import MIMEText
from googleapiclient.discovery import build as build_service
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials

SCOPES = ["https://mail.google.com/"]

configs = {
    "data_dir": os.path.join(os.path.expanduser("~"), ".local/share/atina/server"),
    "token_filename": "gmail_token.json",
    "secret_filename": "",
    "sender_email_addr": ""
}

argparser = argparse.ArgumentParser()

def parse_configs(config_path: str):
    if not os.path.exists(config_path):
        print("Warning: config file doesn't exist, use default configs.")
        return

    parser = configparser.ConfigParser()
    parser.read(config_path)

    if parser.has_section("gmail"):
        if parser.has_option("gmail", "data_dir"):
            data_dir = parser["gmail"]["data_dir"]
            if len(data_dir) != 0:
                configs["data_dir"] = data_dir
        if parser.has_option("gmail", "token_filename"):
            token_filename = parser["gmail"]["token_filename"]
            if len(token_filename) != 0:
                configs["token_filename"] = token_filename
        if parser.has_option("gmail", "secret_filename"):
            secret_filename = parser["gmail"]["secret_filename"]
            if len(secret_filename) != 0:
                configs["secret_filename"] = secret_filename
        if parser.has_option("gmail", "sender_email_addr"):
            sender_email_addr = parser["gmail"]["sender_email_addr"]
            if len(sender_email_addr) != 0 and sender_email_addr.find("@gmail.com") != -1:
                configs["sender_email_addr"] = sender_email_addr

def auth_gmail_api(token_path: str, secret_path: str):
    creds = None
    if os.path.exists(token_path):
        with open(token_path, 'r') as token:
            creds = Credentials.from_authorized_user_file(token_path, SCOPES)

    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        elif os.path.exists(secret_path):
            flow = InstalledAppFlow.from_client_secrets_file(secret_path, SCOPES)
            creds = flow.run_local_server(port=0)
        else:
            raise Exception("secret file not exists")
        
        if not os.path.exists(os.path.dirname(token_path)):
            os.makedirs(os.path.dirname(token_path))
        with open(token_path, 'w') as token:
            token.write(creds.to_json())

    return build_service('Gmail', 'v1', credentials=creds, static_discovery=False)

def create_email(reciever_email_addr: str, subject: str, html_content: str):
    mail = MIMEText(html_content, "html", 'utf-8')
    mail["from"] = configs["sender_email_addr"]
    mail["to"] = reciever_email_addr
    mail["subject"] = subject
    return {"raw": urlsafe_b64encode(mail.as_bytes()).decode()}

def send_email(service, reciever_email_addr: str, subject: str, html_content_path: str):
    if not os.path.exists(html_content_path):
        raise Exception("html content file not exists")
    
    with open(html_content_path, 'r') as content:
        html_content = content.read()

    return service.users().messages().send(
        userId = "me",
        body = create_email(reciever_email_addr, subject, html_content)
    ).execute()

def setup_args():
    arg_group = argparser.add_mutually_exclusive_group()
    arg_group.add_argument("--auth-only", default=False, action="store_true", help="Authenticate only")
    arg_group.add_argument("--send", nargs=3, metavar=tuple(["TO", "SUBJECT", "HTML_FILE"]), type=str, help="Send an email with the html content in the given file")

def main():
    parse_configs(os.path.join(os.path.dirname(os.path.abspath(__file__)), "gmail.cfg"))
    setup_args()

    if len(sys.argv) > 1:
        args = argparser.parse_args()
        service = auth_gmail_api(os.path.join(configs["data_dir"], configs["token_filename"]), os.path.join(configs["data_dir"], configs["secret_filename"]))
        if args.auth_only:
            return
        elif args.send:
            send_email(service, args.send[0], args.send[1], args.send[2])
        else:
            argparser.print_help()
    else:
        argparser.print_help()

if __name__ == "__main__":
    main()
