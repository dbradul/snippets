===================================================
SQL update from one Table to another based on a ID match
(https://bit.ly/2knFduo)
===================================================
----------
INSERT INTO public.shipment_carrier_service_type(internal_code, 
            carrier_id, internal_id, name)
VALUES 
('DHL SmartMail Parcel Ground', 1, '', 'ground'),
('DHL SmartMail Parcel Plus Grou', 1, '', 'ground_plus'),
('DHL SmartMail Parcel Return Gr', 1, '', 'returned');

----------
UPDATE
    public.shipment_invoice_line il
SET
    service_type_id=st.id
FROM
    public.shipment_carrier_service_type st
WHERE 
    il.service_type=st.name;
