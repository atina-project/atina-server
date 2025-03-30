# Email Service provided by Gmail API

This directory contains a python script which sends Emails with Gmail API. It is useful when your server is blocked from SMTP servers of your Email service provider.

First, follow the guide in [SETUP_GMAIL_API.md](./SETUP_GMAIL_API.md) to get your Gmail API credentials.

Then, create your own configuration file based on the `gmail.cfg.in` file. Your config file should be named as `gmail.cfg` and be placed under the same directory of `gmail.py`. Put your credentials under the data folder you chose in your config. (If you enable `ATINA_SERVER_USE_BUILTIN_GMAIL`, the config file should be created automatically on installation.)

After that, run:

```sh
python3 gmail.py --auth-only
```

It will validate your credentials and create a token file.

Finally, write a script which sends email with

```sh
python3 gmail.py --send "$EMAIL_RECEIVER" "$EMAIL_SUBJECT" "$EMAIL_PATH"
```

and hook it into your server. The script `send_email.sh` under this directory provides an example & a very basic function.
